#include <iostream>
#include <fstream>
#include <string>
#include <utf8.h>
#include <vector>
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <unordered_set>
#include <algorithm>    // std::random_shuffle
using namespace std;

//Felhasznalando adatbazis fajlok
void SetDataBase(vector<string>& database){
    cout<<"kerem az adatbazisokat, utolso sor: kesz"<<endl;
    string temp="";
    cin>>temp;
    while(temp.compare("kesz")!=0){
        database.push_back(temp);
        cin>>temp;
    }
    return;
}

void FindKanji(vector<string>& database, const char * workdatabase,string fkanji){
    ofstream myfile1;
    myfile1.open(workdatabase,ios::out);
    for(vector<string>::iterator it=database.begin();it!=database.end();it++){
        //cout<<*it<<endl;
        ifstream ifs;
        string kanji;
        string hiragana;
        ifs.open((*it).c_str(),ios::in);
        if(!(ifs.is_open())){
        throw "Fajl nyitas nem sikerult";
        }

        while(!(ifs.eof())){
            ifs>>kanji;
            ifs>>hiragana;
            ifs.ignore(1);
//        int kanalength=utf8::distance(hiragana.begin(),hiragana.end());
//        int kanjilength=utf8::distance(kanji.begin(),kanji.end());

        string::iterator it1=kanji.begin();
        string::iterator it2=hiragana.begin();
        cout<<kanji<<'\t'<<hiragana<<"End"<<endl;

        while((it1!=kanji.end())){
        uint32_t temp1=utf8::next(it1,kanji.end());
        string res1;
        utf8::utf32to8(&temp1,&temp1+1,back_inserter(res1));

        if(res1.compare(fkanji)==0){
            myfile1<<kanji<<'\t'<<hiragana<<endl;
            it1=kanji.end();
        }
        cout<<"kijottem"<<endl;
        }
        cout<<"kanjibol is 、kijottem"<<endl;

    }
    ifs.close();
    cout<<"kovetkezo fajl"<<endl;
    }
    myfile1.close();
}

void FindReading(vector<string>& database, const char * workdatabase,string reading){
    ofstream myfile1;
    myfile1.open(workdatabase,ios::out);
    for(vector<string>::iterator it=database.begin();it!=database.end();it++){
        //cout<<*it<<endl;
        ifstream ifs;
        string kanji;
        string hiragana;
        ifs.open((*it).c_str(),ios::in);
        if(!(ifs.is_open())){
        throw "Fajl nyitas nem sikerult";
        }

        while(!(ifs.eof())){
            ifs>>kanji;
            ifs>>hiragana;
            ifs.ignore(1);


        string::iterator it1=kanji.begin();
        string::iterator it2=hiragana.begin();
        cout<<kanji<<'\t'<<hiragana<<"End"<<endl;

        while((it2!=hiragana.end())){
        string tempreading="";
        //furigana
        uint32_t temp2=utf8::next(it2,hiragana.end());
        string res2;
        utf8::utf32to8(&temp2,&temp2+1,back_inserter(res2));
        while(res2.compare(u8",")!=0 && it2!=hiragana.end()){

        tempreading.append(res2);
        temp2=utf8::next(it2,hiragana.end());
        res2="";
        utf8::utf32to8(&temp2,&temp2+1,back_inserter(res2));
        }

        if(tempreading.compare(reading)==0){
            myfile1<<kanji<<'\t'<<hiragana<<endl;
            it2=hiragana.end();
        }

        cout<<"kijottem"<<endl;
        }
        cout<<"hiraganabol is 、kijottem"<<endl;

    }
    ifs.close();
    cout<<"kovetkezo fajl"<<endl;
    }
    myfile1.close();
}

void RandomTest(vector<string>& database, const char * workdatabase,const int number){
    //database sorok leszámlálása
    int sumlinenumber=0;
    int rownums[number];
    srand((int)time(0));
        for(vector<string>::iterator it=database.begin();it!=database.end();it++){
        //cout<<*it<<endl;
        ifstream ifs;
        string kanji;
        string hiragana;
        ifs.open((*it).c_str(),ios::in);
        if(!(ifs.is_open())){
        throw "Fajl nyitas nem sikerult";
        }

        while(!(ifs.eof())){
            ifs>>kanji;
            ifs>>hiragana;
            ifs.ignore(1);
            sumlinenumber+=1;


    }
    ifs.close();
    cout<<"kovetkezo fajl"<<endl;
    }


    //number darab véletlen szám generálása
    srand((int)time(0));
    rownums[0]=rand()%sumlinenumber;
    for(int i=1;i<number;i++){
        rownums[i]=rand()%sumlinenumber;
        //van-e azonos
        for(int j=0;j<i;j++){
            if(rownums[j]==rownums[i]){
                rownums[i]=rand()%sumlinenumber;
                j=-1;
            }
        }
        //sort
        int temp;
        for(int j=0;j<i;j++){
            if(rownums[j]>rownums[i]){
                temp=rownums[j];
                rownums[j]=rownums[i];
                rownums[i]=temp;
            }
        }
    }
    //sorok kiírása
    ofstream myfile1;
    myfile1.open(workdatabase,ios::out);
    int linenumber=0;
    int actrow=0;
    for(vector<string>::iterator it=database.begin();it!=database.end();it++){
    //cout<<*it<<endl;
    ifstream ifs;
    string kanji;
    string hiragana;
    ifs.open((*it).c_str(),ios::in);
    if(!(ifs.is_open())){
    throw "Fajl nyitas nem sikerult";
    }
    while(!(ifs.eof())&&(actrow!=number)){
        ifs>>kanji;
        ifs>>hiragana;
        ifs.ignore(1);
        if(linenumber==rownums[actrow]){
            myfile1<<kanji<<'\t'<<hiragana<<endl;
            actrow++;
        }
        linenumber++;
    }
    ifs.close();
    cout<<"kovetkezo fajl"<<endl;
    }

    myfile1.close();
    return;

}

void OneBaseWriter(string database,ostream& myfile1,char& type){
    string kanji;
    string hiragana;
    ifstream ifs;
//    bool prev=false;
    ifs.open(database.c_str(),ios::in);
    if(!(ifs.is_open())){
        throw "Fajl nyitas nem sikerult";
    }

    while(!(ifs.eof())){
        ifs>>kanji;
        ifs>>hiragana;
        ifs.ignore(1);
        ifs.peek();

        string::iterator it1=kanji.begin();
        string::iterator it2=hiragana.begin();
        cout<<kanji<<'\t'<<hiragana<<"End"<<endl;
        myfile1<<"\\mbox{";
        while((it1!=kanji.end())){
        uint32_t temp1=utf8::next(it1,kanji.end());
        string res1;
        utf8::utf32to8(&temp1,&temp1+1,back_inserter(res1));

        if(res1.compare(u8"\"")==0){
             int counter=0;
             myfile1<<"\\ruby{";

             temp1=utf8::next(it1,kanji.end());
             res1="";
             utf8::utf32to8(&temp1,&temp1+1,back_inserter(res1));
             while(res1.compare(u8"\"")!=0 && it1!=hiragana.end()){
                counter++;
                myfile1<<"\\framebox[1.1 cm][c]{";

                switch(type){
                case 'k':
                    myfile1<<"\\phantom{"<<res1<<"}";
                    break;
                default:
                    myfile1<<res1;
                }

                myfile1<<"}"; //close framebox

                res1="";
                temp1=utf8::next(it1,kanji.end());
                utf8::utf32to8(&temp1,&temp1+1,back_inserter(res1));

             }

             myfile1<<"}"; //close ruby 1 {}
             double rubywidth=counter*0.9;
             myfile1<<"{"; //open ruby 2 {
             myfile1<<"\\makebox["<<rubywidth<<" cm][s]{";

            uint32_t temp2=utf8::next(it2,hiragana.end());
            string res2;
            utf8::utf32to8(&temp2,&temp2+1,back_inserter(res2));

            while(res2.compare(u8",")!=0 && it2!=hiragana.end()){
                switch(type){
                    case 'r':
                        myfile1<<" \\phantom{"<<res2<<"}";
                        break;
                    default:
                        myfile1<<" "<<res2;
                }

            //cout<<res2<<"utana";
            temp2=utf8::next(it2,hiragana.end());
            res2="";
            utf8::utf32to8(&temp2,&temp2+1,back_inserter(res2));
            //cout<<res2<<endl;
            //cout<<"ellenorzes:"<<res2.compare(u8",")<<endl;
            }
            myfile1<<" }"; //close makebox
            myfile1<<"}"; //close ruby 2 {}

        }

        else if(res1.compare(u8";")==0){
            myfile1<<"}\\hspace{1 pt}";//close mbox
            myfile1<<"\\mbox{"; //open mbox
        }

        else{
        //furigana
        uint32_t temp2=utf8::next(it2,hiragana.end());
        string res2;
        utf8::utf32to8(&temp2,&temp2+1,back_inserter(res2));

        if(res1.compare(res2)==0){
            //hiragana egysegeknek egyben kell maradni
            //ha az elozo nem ilyen volt
//            if(!prev){
//            myfile1<<"}\\hspace{1 pt}"; //close mbox
//             myfile1<<"\\mbox{"; //open mbox for hiragana insert
//           }
            myfile1<<"\\makebox[0.9 cm][c]{"<<res1<<"}";

            //vesszo beolvasasa
            temp2=utf8::next(it2,hiragana.end());
            res2="";

            //mi fog következni, ha van még
//            if(it1!=kanji.end()){
//            uint32_t tempk=utf8::peek_next(it1,kanji.end());
//            uint32_t temph=utf8::peek_next(it2,hiragana.end());
//            string resk,resh;
//            utf8::utf32to8(&tempk,&tempk+1,back_inserter(resk));
//            utf8::utf32to8(&temph,&temph+1,back_inserter(resh));
            //ha a kov. nem hiragana lesz
//            if(resk.compare(resh)!=0){
//                myfile1<<"}\\hspace{1 pt}"; //close hiragana mbox
 //               myfile1<<"\\mbox{"; //open mbox for next word
//            }
 //           }
 //           prev=true; //hiraganat irtunk ki, nem kanjit

        }

        else{
        myfile1<<"\\ruby{\\framebox[1.1 cm][c]{";

        switch(type){
            case 'k':
                myfile1<<"\\phantom{"<<res1<<"}";
                break;
            default:
                myfile1<<res1;
        }

 //       prev=false; //kanjit irtunk ki nem hiraganat

        myfile1<<"}}{";
        //cout<<res1<<'\t';

        while(res2.compare(u8",")!=0 && it2!=hiragana.end()){
        switch(type){
            case 'r':
                myfile1<<"\\phantom{"<<res2<<"}";
                break;
            default:
                myfile1<<res2;
        }

        //cout<<res2<<"utana";
        temp2=utf8::next(it2,hiragana.end());
        res2="";
        utf8::utf32to8(&temp2,&temp2+1,back_inserter(res2));
        //cout<<res2<<endl;
        //cout<<"ellenorzes:"<<res2.compare(u8",")<<endl;


        }
        myfile1<<"}"; //close ruby2 {}
        }
        cout<<"kijottem"<<endl;
        } //ha nem specko furiganas szo
        }
        myfile1<<"}、\\vspace{3 pt} ";
        cout<<"kanjibol is 、kijottem"<<endl;

    }
    ifs.close();
    return;
}

void Writer(vector<string>& database,ostream& output,char& type){
    for(vector<string>::iterator it=database.begin();it!=database.end();it++){
        OneBaseWriter(*it,output,type);
    }
    return;
}

void Shuffle(vector<string>& database, const char * shuffdataname){
    vector<string> lines;
    //beolvassuk az adatokat
    for(vector<string>::iterator it=database.begin();it!=database.end();it++){
        ifstream ifs;
        string line;
        ifs.open((*it).c_str(),ios::in);
        if(!(ifs.is_open())){
        throw "Fajl nyitas nem sikerult";
        }

        while(getline(ifs,line)){
            lines.push_back(line);
        }
        ifs.close();
        cout<<"kovetkezo fajl"<<endl;
    }//database end

    //shuffling
    random_shuffle ( lines.begin(), lines.end() );

    //print
    ofstream myfile1;
    myfile1.open(shuffdataname,ios::out);

    for(vector<string>::iterator it=lines.begin();it!=lines.end();it++){
        myfile1<<*it<<endl;
    }

    myfile1.close();
    return;
}

void MultiKiller(vector<string>& database, const char * cutdatabase){
    unordered_set<string> prelines;
    //beolvassuk az adatokat
    for(vector<string>::iterator it=database.begin();it!=database.end();it++){
        ifstream ifs;
        string line;
        ifs.open((*it).c_str(),ios::in);
        if(!(ifs.is_open())){
        throw "Fajl nyitas nem sikerult";
        }

        while(getline(ifs,line)){
            prelines.insert(line);
        }
        ifs.close();
        cout<<"kovetkezo fajl"<<endl;
    }//database end

    //kiírjuk
    //print
    ofstream myfile1;
    myfile1.open(cutdatabase,ios::out);

    for(unordered_set<string>::iterator it=prelines.begin();it!=prelines.end();it++){
        myfile1<<*it<<endl;
    }

    myfile1.close();
    return;

}

void SetTask(char & task,string & outdir,vector<string>& database){
    //main task
    switch(task){
        case 'w':
            break;
        case 'r':{
            int number;
            cout<<"hany szo kell?"<<endl;
            cin>>number;
            RandomTest(database,(outdir+"/workdata3.txt").c_str(),number);
            database.erase(database.begin(),database.end());
            database.push_back(outdir+"/workdata3.txt");
            break;}
        case 'k':{
            string fkanji;
            cout<<"kerem a keresendo kanjit"<<endl;
            cin>>fkanji;
            FindKanji(database,(outdir+"/workdata3.txt").c_str(),fkanji);
            database.erase(database.begin(),database.end());
            database.push_back(outdir+"/workdata3.txt");
            break;}
        case 'h':{
            string reading;
            cout<<"kerem a keresendo olvasatot"<<endl;
            cin>>reading;
            FindReading(database,(outdir+"/workdata3.txt").c_str(),reading);
            database.erase(database.begin(),database.end());
            database.push_back(outdir+"/workdata3.txt");
            break;}

    }//switch task

    return;
}



int main()
{
    vector<string> database;
    string outdir;
    char task='s';
    char writetype='s';
    char shuffle='n';
    char key='y';
    //string fkanji;
    //string reading;

    cout<<"kerem a kimeneti konyvtarat"<<endl;
    cin>>outdir;
    SetDataBase(database);
    //adatbazis fajlnevek - SetDataBase ellenőrzése
    cout<<"beolvasando fajlok"<<endl;
    for(vector<string>::iterator it=database.begin();it!=database.end();it++){
        cout<<*it<<endl;
    }

    cout<<"Kerem a feladatot"<<endl;
    cout<<"w: csak kiírás"<<endl;
    cout<<"r: random valasztott kanji"<<endl;
    cout<<"k: kanjit keres"<<endl;
    cout<<"h: olvasatot keres"<<endl;
    cin>>task;

    cout<<endl;
    cout<<"Kiiras tipusa"<<endl;
    cout<<"s: minden latszik"<<endl;
    cout<<"k: kanji nem latszik"<<endl;
    cout<<"r: furigana nem latszik"<<endl;
    cin>>writetype;

    cout<<"Shuffle option"<<endl;
    cout<<"s: kever"<<endl;
    cout<<"egyeb: nem kever"<<endl;
    cin>>shuffle;

    if(writetype!='s'){
        cout<<"Kell javito kulcs?"<<endl;
        cout<<"n: nem"<<endl;
        cout<<"egyeb: general kulcsot is"<<endl;
        cin>>key;
    }
    else{ //amúgy is latszik minden, nem kell plusz peldany
        key='n';
    }

    //main task
    SetTask(task,outdir,database);

    //after work
    //kill multiple occurence
    //default for task!=w (not simple writeout)
    //ask if simple writeout (w) with shuffle (s)
    //not possible for simple writeout (w) without shuffle (n or else)
    if(task=='w' && shuffle=='s'){
        cout<<"Remove multiple occurence?"<<endl;
        cout<<"w: do not remove"<<endl;
        cout<<"else: remove"<<endl;
        cin>>task;
    }
    if(task!='w'){
        MultiKiller(database,(outdir+"/cutdata.txt").c_str());
        database.erase(database.begin(),database.end());
        database.push_back(outdir+"/cutdata.txt");
    }

    //after work
    //shuffle if needed
    if(shuffle=='s'){
                Shuffle(database,(outdir+"/shuffdata.txt").c_str());
                database.erase(database.begin(),database.end());
                database.push_back(outdir+"/shuffdata.txt");
    }

    //write out
    ofstream myfile1;
    myfile1.open((outdir+"/feladat.tex").c_str(),ios::out);
    Writer(database,myfile1,writetype);
    myfile1.close();

    //javito kulcsot is irhatunk
    if(key!='n'){
        if(writetype!='s'){writetype='s';}
        myfile1.open((outdir+"/javito.tex").c_str(),ios::out);
        Writer(database,myfile1,writetype);
        myfile1.close();
    }

    if (myfile1.is_open()){
        myfile1.close();
    }



    //cout<<"keresendo kanji:"<<endl;
    //cin>>fkanji;

    //cout<<"keresendo olvasat"<<endl;
    //cin>>reading;

    //FindKanji(database,"./workdata.txt",fkanji);
    //FindReading(database,"./workdata2.txt",reading);
    //RandomTest(database,"./workdata3.txt",5);

//    string filename;
//    string outname;
//    string kanji;
//    string hiragana;
//
//    cout<<"kerem a fajlnevet"<<endl;
//    cin>>filename;
//    cout<<"kerem a kimeneti nevet"<<endl;
//    cin>>outname;
//
//    ofstream myfile1;
//    myfile1.precision(6);
//    myfile1.open((outname).c_str(),ios::out);
//
//
//    ifstream ifs;
//    ifs.open((filename).c_str(),ios::in);
//    if(!(ifs.is_open())){
//        throw "Fajl nyitas nem sikerult";
//    }
//
//    while(!(ifs.eof())){
//        ifs>>kanji;
//        ifs>>hiragana;
//        ifs.ignore(1);
//        int kanalength=utf8::distance(hiragana.begin(),hiragana.end());
//        int kanjilength=utf8::distance(kanji.begin(),kanji.end());
//
//        string::iterator it1=kanji.begin();
//        string::iterator it2=hiragana.begin();
//        cout<<kanji<<'\t'<<hiragana<<"End"<<endl;
//        myfile1<<"\\mbox{";
//        while((it1!=kanji.end())){
//        uint32_t temp1=utf8::next(it1,kanji.end());
//        string res1;
//        utf8::utf32to8(&temp1,&temp1+1,back_inserter(res1));
//
//
//        //furigana
//        uint32_t temp2=utf8::next(it2,hiragana.end());
//        string res2;
//        utf8::utf32to8(&temp2,&temp2+1,back_inserter(res2));
//
//        if(res1.compare(res2)==0){
//            myfile1<<"\\makebox[0.9 cm][c]{"<<res1<<"}";
//            res2="";
//            //vesszo beolvasasa
//            temp2=utf8::next(it2,hiragana.end());
//
//        }
//
//        else{
//        myfile1<<"\\ruby{\\framebox[1.1 cm][c]{"<<res1<<"}}{";
//        cout<<res1<<'\t';
//
//        while(res2.compare(u8",")!=0 && it2!=hiragana.end()){
//
//        myfile1<<res2;
//        cout<<res2<<"utana";
//        temp2=utf8::next(it2,hiragana.end());
//        res2="";
//        utf8::utf32to8(&temp2,&temp2+1,back_inserter(res2));
//        cout<<res2<<endl;
//        cout<<"ellenorzes:"<<res2.compare(u8",")<<endl;
//
//
//        }
//        myfile1<<"}";
//        }
//        cout<<"kijottem"<<endl;
//        }
//        myfile1<<"}、\\vspace{3 pt} ";
//        cout<<"kanjibol is 、kijottem"<<endl;
//
//    }
//    ifs.close();
//    myfile1.close();
//
    cout <<"Kesz"<<endl;


    return 0;
}
