#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <fstream>

#define VAR uint32_t    						///Size of the problem
#define MINI uint16_t    						///Index size //BUG with uint_8
#define HOMELESS (~(VAR)0)  					///This resident is homeless right now (updated from ((VAR)-1) )
#define VARMAX (HOMELESS-1)						///Maximum usable value of a VAR

using namespace std;

MINI B=1;   									///Buildings
MINI M=2;   									///Room's repetitive properties - Mod
MINI N_RT=2;									///Room types
VAR N_D=0;  									///Number of rooms
VAR N_X=0;  									///Number of residents

map<VAR,set<VAR>> Dx;   						///Room pool - domain / people<personID, room_pool<roomID>>
vector<VAR> X;      							///Residents
vector<MINI> RT;    							///Rooms with type

vector< vector<bool> > C_M; 					///Room's repetitive properties constraint
bool M_def = true;      						///Default value for M needs
vector<pair<MINI,MINI>> RP = { {4,3}, {3,6} };  ///Room's Properties - Count/Capacity
vector< vector<bool> > C_RT;					///Room type constraint
bool RT_def = true;     						///Default value for room type
vector< set<VAR> > C_F;  						///Requested roommates / friend constraint
vector< set<VAR> > C_E;  						///Rejected roommates / enemy constraint

struct State{
    State();
    State(VAR x, map<VAR,set<VAR>> d) : X_actual(x), D_actual(d){};
    VAR X_actual;
    map<VAR,set<VAR>> D_actual;
};

stack<State> SBuilder;							
unsigned long long StepCounter = 0;

void ReadData();
bool Solve();
void WriteSolution();
void WriteFailure();

int main(){
    ReadData();
    if( Solve() ) WriteSolution();
    else WriteFailure();
    cout << "Az algoritmus lefutott " << StepCounter << " lepessel.\n";
    return 0;
}

void ReadData(){
    MINI tmp1, tmp2;
    VAR tmp3, tmp4;
    char tmpChar;
    bool pre = true;
    ifstream data("input.txt");
    while(pre and data>>tmpChar) switch(tmpChar){
    case 'C': pre=false; break;
    case 'B': data>>B; break;
    case 'M': data>>M; break;
    case 'R':
        data>>N_RT;
        RP.clear();
        for(MINI i=0; i<N_RT; i++){
            data >> tmp1 >> tmp2; 		///How many rooms? Capacity?
            RP.push_back( make_pair(tmp1,tmp2) );
        } break;
    }
    for( auto& room : RP){ N_D += room.first; N_X += room.first*room.second; }
    N_D *= B*M; N_X *= B*M;
    cout << "Emberek szama: " << N_X << " \nSzobak szama: " << N_D << endl << endl;

    C_M.clear();    C_M.resize( N_X, vector<bool>(M,M_def) );
    C_RT.clear();   C_RT.resize( N_X, vector<bool>(N_RT,RT_def) );
    C_F.clear();    C_F.resize( N_X, set<VAR>() );
    C_E.clear();    C_E.resize( N_X, set<VAR>() );
    while(data>>tmpChar) switch(tmpChar){
        case 'M':
            data>>tmp3;
            for(VAR i=0; i<tmp3; i++){
                data >> tmp4 >> tmp1;    /// Which room is okay or not okay for a person
                C_M[tmp4][tmp1] = !M_def;
            } break;
        case 'T':
            data>>tmp3;
            for(VAR i=0; i<tmp3; i++){
                data >> tmp4 >> tmp1;   /// Which room can a person occupy - has the right to occupy
                C_RT[tmp4][tmp1]= !RT_def;
            } break;
        case 'F':
            data>>tmp1;
            for(MINI i=0; i<tmp1; i++){
                data >> tmp3 >> tmp4;
                C_F[tmp3].insert(tmp4); /// X wants to be with Y
                C_F[tmp4].insert(tmp3); /// Let this be a mutual request 
            } break;
        case 'E':
            data>>tmp1;
            for(MINI i=0; i<tmp1; i++){
                data >> tmp3 >> tmp4;
                C_E[tmp3].insert(tmp4); /// X doesn't want to be with Y
                C_E[tmp4].insert(tmp3); /// Let this also be a mutual request 
            } break;
    }
    data.close();
}

bool CanOccupy(VAR homie, VAR room){
    if( C_M[homie][ room%M ] )  		/// Is the facing of the room okay?
        if( C_RT[homie][ RT[room] ] )   /// Has the person the right to occupy it?
            return true;
    return false;
}
void Init(){
    MINI roomType=0;

    RT.clear();
    for(const auto& room : RP) RT.resize( RT.size()+B*M*room.first , roomType++);

    X.clear(); X.resize( N_X, HOMELESS );
    for(VAR h=0; h<N_X; h++) 			/// h - homelesses
        for(VAR r=0; r<N_D;  r++)
            if( CanOccupy(h,r) ) Dx[h].insert(r);

}
VAR MVR(const map<VAR,set<VAR>>&);
VAR OrderDomainValues(VAR, set<VAR>&);	///For whom and from which domain?
bool incompatibleConstraint(VAR);
State StepBuilder(const State&);
bool Solve(){
    Init();

    SBuilder.push(State( MVR(Dx), Dx ));

    while( !SBuilder.empty() ){
        VAR homie = SBuilder.top().X_actual;

        ///We try one value
        X[homie] = OrderDomainValues(homie, SBuilder.top().D_actual[homie] );
        if( X[homie]==HOMELESS ){ 		///There's no more value
                SBuilder.pop(); continue;
        }else{ 							///There is a value
            StepCounter++;
            ///Are there incompatible constraints? If yes, then it will go to the next value with a simple continue;
            if( incompatibleConstraint(homie) ) continue;
        }

        if( SBuilder.size()==X.size() ) return true;

        SBuilder.push( StepBuilder( SBuilder.top() ) );
    }
    ///There wasn't any solution and the stack is empty...
    return false;
}

VAR OrderDomainValues(VAR homie, set<VAR>& domain){
    ///valamilyen sorrend (most az elso lehetseges)
    EZ_MI_EZ?
    VAR value = HOMELESS;
    if( domain.size() >0  ){
        value = *domain.begin();
        domain.erase(domain.begin());	///This function shrinks the size of the domain
    }
    return value;
}
bool incompatibleConstraint(VAR x){		///For example: is there any room left for a new person?
    MINI roomMates=0;
    for(VAR Xvalue : X) if(Xvalue==X[x]) roomMates++; ///How many of them are in the room?
    if( RP[RT[X[x]]].second < roomMates ) return true;

    return false;
}

map<VAR,set<VAR>> DomainBuilder(const State&);
State StepBuilder(const State& oldState){
    map<VAR,set<VAR>> newDomain = DomainBuilder(oldState);
    return State( MVR(newDomain), newDomain );
}
VAR MVR(const map<VAR,set<VAR>>& D_actual){
    VAR newHomie, minDsize = N_D+1;		/// N_D became the D_max 
    for(const auto& mit : D_actual) if( X[mit.first]==HOMELESS )
        if( mit.second.size() < minDsize ){
            minDsize = mit.second.size();
            newHomie = mit.first;
        }

    return newHomie;
}
void AC3(VAR x, map<VAR,set<VAR>>& D_actual){
    queue<VAR> friends;
    for(const auto& xFriend :C_F[x]) friends.push(xFriend);
    while( !friends.empty() ){
        if( D_actual[ friends.front() ].erase( X[x] ) >0 ){
            if( D_actual[ friends.front() ].size() >0 ){
                D_actual[ friends.front() ].clear();
                for(const auto& yFriend :C_F[friends.front()]) friends.push( yFriend );
            }
            D_actual[friends.front()].insert( X[x] );
        }
        friends.pop();
    }
}
map<VAR,set<VAR>> DomainBuilder(const State& oldState){
    map<VAR,set<VAR>> D_actual = oldState.D_actual;

    VAR homie = oldState.X_actual;
    for(const auto& enemies : C_E[homie]) D_actual[enemies].erase(X[homie]); ///Forward check

    AC3( homie, D_actual );

    D_actual[homie].clear();			///Optimisation
    return D_actual;
}

void WriteSolution(){
    map<VAR,set<VAR>> Assignment;
    for(VAR x=0; x<X.size(); x++) Assignment[X[x]].insert(x);

    cout << "A szobabeosztas:\n";
    for(const auto& mit : Assignment){
        cout << mit.first << ". szoba  ( ";
        for(const auto& sit : mit.second)
            cout << sit << " ";
        cout << ")\n";
    }
}
void WriteFailure(){
    cout << "Nincs lehetseges szobabeosztas.\n";
}
