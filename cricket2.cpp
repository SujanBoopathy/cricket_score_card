#include<iostream>
#include<vector>
#include<map>
using namespace std;
bool matchStatus(int a,int b);
bool matchResult(int a,int b);
void update(map<int,int> bat);

class Team{
    public :
        string teamName;
        vector<string> batsman;
        vector<string> bowler;
        int bRuns[3]={0};
        int bBalls[3]={0};

        int bowlerBalls[2]={0};
        int bowlerRuns[2]={0};
        int bowlerWicket[2]={0};


        int teamRuns=0,wickets=0,extra=0,over=0,balls=0;
        void setTeamName(string name){
            teamName=name;
        }   

        int batsmansSR[3]={0};
        int batsmanC[3]={0};

        int bowlerSR[2]={0};
        int bowlerC[2]={0};

        void calculateBatBowl(){
            for(int i=0;i<3;i++){
                batsmansSR[i]=bRuns[i]/bBalls[i];
            }
            for(int i=0;i<3;i++){
                batsmanC[i]=bRuns[i]/teamRuns;
            }
            for(int i=0;i<2;i++){
                bowlerSR[i]=bowlerWicket[i]/wickets;
                bowlerC[i]=bowlerSR[i]*100;
            }
        }  
         
        void showStat(){
            calculateBatBowl();
            
            for(int i=0;i<3;i++){
                cout<<batsman[i]<<"--"<<batsmansSR[i]<<"SR --"<<batsmanC[i]<<" Contribution"<<endl;
            }
            for(int i=0;i<2;i++){
                cout<<bowler[i]<<"--"<<bowlerSR[i]<<"SR --"<<bowlerC[i]<<" Contribution"<<endl;
            }
        }


        void showBatting(){
            cout<<"Batting :"<<endl;
            for(int i=0;i<3;i++){
                cout<<batsman[i]<<" -- "<<bRuns[i]<<"runs -- "<<bBalls[i]<<"balls"<<endl;
            }
            cout<<"Innings Extras - "<<extra<<" runs "<<endl;
        }

        void showBowling(){
            for(int i=0;i<2;i++){
                cout<<bowler[i]<<"--"<<bowlerBalls[i]/6<<" . "<<bowlerBalls[i]%6<<" Overs --"<<bowlerRuns[i]<<"/"<<bowlerWicket[i]<<endl;
            }
        }

};

int main(){
    Team t1,t2;
    string s;
    cin>>t1.teamName>>t2.teamName;
    cout<<"Enter team 1 players :"<<endl;
    for(int i=0;i<3;i++){
        cin>>s;
        t1.batsman.push_back(s);
    }
    for(int i=0;i<2;i++){
        cin>>s;
        t1.bowler.push_back(s);
    }
    cout<<"Enter team 2 player"<<endl;
    for(int i=0;i<3;i++){
        cin>>s;
        t2.batsman.push_back(s);
    }
    for(int i=0;i<2;i++){
        cin>>s;
        t2.bowler.push_back(s);
    }

    //first innings input module
    int striker=0,nonStriker=1;
    int bowl=0;
    cout<<"Enter 1st innings details :"<<endl;
    for(int i=0;i<5;i++){
        //bowler
        if(i%2==0)
            bowl=0;
        else
            bowl=1;
        int balls=6;
        while(balls){
            cin>>s;
            if(s=="0Wd" || s=="0Nb"){
                //batting 
                t1.bBalls[striker]++;
                t1.teamRuns++;
                t1.extra++;

                //bowling
                t2.bowlerRuns[bowl]++;
            }
            else if(s>="0" && s<="6"){
                int temp=s[0]-'0';
                t1.bRuns[striker]+=temp;
                t1.bBalls[striker]++;
                if(temp%2!=0){
                    swap(striker,nonStriker);
                }
                
                t1.teamRuns+=temp;
                balls--;
                t1.balls++;


                //bowler
                t2.bowlerBalls[bowl]++;
                t2.bowlerRuns[bowl]+=temp;
            }
            else if(s=="W"){
                t1.bBalls[striker]++;
                t1.wickets++;
                balls--;
                t1.balls++;
                striker=2;

                //bowler
                t2.bowlerWicket[bowl]++;
            }
            if(t1.wickets==2){
                break;
            }
            
        }
        swap(striker,nonStriker);
        if(t1.wickets==2){
                break;
        }
        t1.over++;
        
    }
    if(t1.balls==6){
        t1.over++;
        t1.balls=0;
    }
    

    //second innings input module
    striker=0;
    nonStriker=1;
    bowl=0;
    cout<<"Enter 2nd innings details :"<<endl;
    for(int i=0;i<5 && !matchStatus(t1.teamRuns,t2.teamRuns);i++){
        //bowler
        if(i%2==0)
            bowl=0;
        else
            bowl=1;
        int balls=6;
        while(balls){
            cin>>s;
            if(s=="0Wd" || s=="0Nb"){
                t2.bBalls[striker]++;
                t2.teamRuns++;
                t2.extra++;

                //bowling
                t1.bowlerRuns[bowl]++;
            }
            else if(s=="1Nb"){
                t2.bBalls[striker]++;
                t2.teamRuns++;
                t2.extra+=2;
                swap(striker,nonStriker);

                //bowling
                t1.bowlerRuns[bowl]+=2;
            }
            else if(s>="0" && s<="6"){
                int temp=s[0]-'0';
                t2.teamRuns+=temp;
                t2.bRuns[striker]+=temp;
                t2.bBalls[striker]++;
                if(temp%2!=0){
                    swap(striker,nonStriker);
                }
                
                balls--;
                t2.balls++;

                //bowler
                t1.bowlerBalls[bowl]++;
                t1.bowlerRuns[bowl]+=temp;
            }
            else if(s=="W"){
                t2.bBalls[striker]++;
                striker=2;
                t2.wickets++;
                balls--;
                t2.balls++;

                //bowler
                t1.bowlerWicket[bowl]++;
            }
            if(t2.wickets==2 || matchStatus(t1.teamRuns,t2.teamRuns)){
                break;
            }
        }
        swap(striker,nonStriker);
        if(t2.wickets==2 || matchStatus(t1.teamRuns,t2.teamRuns)){
                break;
        }
        t2.over++;
        
    }
    if(t2.balls==6){
        t2.over++;
        t2.balls=0;
    }


    //Result 
    cout<<"Team 1"<<endl;
    cout<<t1.teamRuns<<"/"<<t1.wickets;
    if(matchResult(t1.teamRuns,t2.teamRuns)) cout<<"\tWon";
    else if(t1.wickets==2) cout<<"\t(All out)";
    cout<<"\t"<<t1.balls/6<<"."<<t1.balls%6<<endl;

    cout<<"\nTeam 2"<<endl;
    cout<<t2.teamRuns<<"/"<<t2.wickets;
    if(matchResult(t2.teamRuns,t1.teamRuns)) cout<<"\tWon";
    else if(t2.wickets==2) cout<<"\t(All out)";
    cout<<"\t"<<t2.balls/6<<"."<<t2.balls%6<<endl;
    



    //batsman score
    cout<<"\n\nTeam 1 batsman :\n";
    t1.showBatting();

    cout<<"\n\nTeam 2 batsman :\n";
    t2.showBatting();

    //bowling score
    cout<<"\n\nTeam 1 bowling :"<<endl;
    t1.showBowling();

    cout<<"\n\nTeam 2 bowling :"<<endl;
    t2.showBowling();

    //contribution
    cout<<"Team 1"<<endl;
    t1.showStat();

    cout<<"\n\nTeam 2"<<endl;
    t2.showStat();

    return 0;
}

bool matchStatus(int a,int b){
    if(a>=b){
        return false;
    }
    else{
        return true;
    }
}

bool matchResult(int a,int b){
    if(a>b)
    return true;
    else
    return false;
}

