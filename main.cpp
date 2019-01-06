#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct node{
    node *next;
    node *prev;
    int key;
};


bool isArgsInvalid = false;
string dataSource = "dane.txt";
int action = 0; 
int key = 0; 
int index = 0;
int *tablica;
int static arrSize;

node* head;


void printParam(){
    cout <<isArgsInvalid<< endl;
    cout <<dataSource<< endl;
    cout <<action<< endl;
    cout <<key<< endl;
    cout <<index<< endl;
}
void banner(){
    cout<<"LISTY - KLAUDIA KOHNKE"<< endl;
}

void usage(){
    cout <<"[*]Parametry programu:" <<endl;
    cout <<"[*] --help wyswietla te wiadomosc" <<endl;
    cout <<"[*] --dane <dane.txt> pobiera dane ze wskazanego pliku, plik MUSI znajdowac sie w tym samym folderze co program"<<endl;
    cout <<"[*] --dodaj-glowa <liczba>" <<endl;
    cout <<"[*] --dodaj-ogon >liczba>" <<endl;
    cout <<"[*] --znajdz <liczba> zwraca indeks pierwszego wystapienia elementu w liscie" <<endl;
    cout <<"[*] --dodaj <liczba> <indeks> dodaje element we wskazane miejsce w liscie" <<endl;
    cout <<"[*] --usun <indeks> usuwa element z wybranego miejsca w liscie" <<endl;
    cout <<"[*] --usun-glowe" <<endl;
    cout <<"[*] --usun-ogon" <<endl;
    cout <<"[*] --wypisz" <<endl;
}

void printArgsError( vector<string> _args){
    cout << "[*] Nieprawidlowe parametry programu: ";
    for (int i = 0; i < _args.size(); ++i) {
        cout << _args[i] + " ";
    }
    usage();

}

int * stringToDynamArray(string _str, string _delimeter , int _arraySize){
    size_t pos = 0;
    string token;
    int *a = new int[_arraySize];
    int i =0;

    while ((pos = _str.find(_delimeter)) != std::string::npos) {
        token = _str.substr(0, pos);
        a[i] = atoi(token.c_str());
        i++;
        _str.erase(0, pos + _delimeter.length());
    }

    return a;
}

node* SearchIndex(node *_head, int _ind){
    cout<<"[!] SEARCH-INDEX"<<endl;
    for (int i = 0; i < _ind; ++i) { 
        if(_head->next !=NULL){ 
            _head = _head->next; 
        }
        else {
            cout << "Takiego indeksu nie ma na liscie!" << endl;
            break;
        }
    }
    return _head;
}

void RemoveTail(node* _head){
    cout<<"[!] DELETE-TAIL"<<endl;
    while(_head->next != NULL){
        _head = _head->next; 
    }
    _head->prev->next = NULL; 
    _head->prev = NULL; 
    _head = NULL; 
}

node* RemoveHead(node* _head){
    cout<<"[!] DELETE-HEAD"<<endl;
    _head->key = 0; 
    _head = _head->next;
    _head->prev->next = NULL; 
    _head->prev = NULL; 
    return _head; 
}

void DeleteIndex(node *_head, int _ind){
    cout<<"[!] DELETE-INDEX"<<endl;
    _head = SearchIndex(_head,_ind);
    if(_head->next == NULL){
        RemoveTail(_head); 
    }
    else if(_head->prev == NULL){ 
        RemoveHead(_head); 
    }
    else{
        _head->prev->next=_head->next; 
        _head->next->prev=_head->prev; 
        _head->next = NULL;
        _head->prev = NULL;
        _head->key = 0;
    }
}

node* CreateList(int* _tablica, int _arrSize, node *_head){
    cout<<"[!] CREATE-LIST"<<endl;
    for(int i = 0; i < _arrSize; ++i) {
        _head->next = new node;
        _head->key = _tablica[i]; 
        _head->next->prev = _head;  
        _head = _head->next; 
    }
    _head = _head->prev; 
    _head->next = NULL; 
    return head;
}


void PrintList(node *_head){
    int nodeNo = 0;
    cout<<"[!] PRINT-LIST"<<endl;
    while(_head != NULL) {
        cout << "[*] Nr: " << nodeNo;
        nodeNo++;
        cout << "Klucz: ";
        cout << _head->key << endl; 
        _head = _head->next; 
    }
}

void InsertIndex(node *_head, int _key, int _ind) {
    cout << "[!] INSERT-INDEX" << endl;
    _head = SearchIndex(_head, _ind); 
    node *temp = new node; 

    if (_ind == 0) { 
        temp->key = _key;
        temp->prev = NULL;
        temp->next = _head;
        head = temp;

    } else {
        _head->prev->next = temp;
        temp->prev = _head->prev;
        temp->next = _head;
        _head->prev = temp;
        temp->key = _key;

    }
}

void FindIndex(node* _head, int _key){
    cout<<"[!] FIND-INDEX"<<endl;
    int count = 0;
    while(_head->next != NULL && _head->key != _key){ 
        _head = _head->next;
        count++; 
    }
    if(_head->next == NULL && _key != _head->key){
        cout << "[*] Nie znaleziono klucza." << endl;
    }
    else{
        cout << "Klucz znaleziono w indexie nr: " << count <<endl;
    }
}

node* InsertHead(node* _head, int _key){
    cout<<"[!] INSERT-HEAD"<<endl;
    _head->prev = new node; 
    _head->prev->next=_head;
    _head->prev->key=_key; 
    return head->prev; 
}

void InsertTail(node* _head, int _key) {
    cout << "[!] INSERT-TAIL" << endl;
    while (_head->next != NULL) { 
        _head = _head->next; 
    }
    node * temp = new node; 
    temp->key = _key;
    temp->next = NULL;
    _head->next = temp;
    temp->prev = _head;
}

void pobierzDane(){
    arrSize = 0;
    string temp = "";
    fstream plik;
    plik.open( dataSource.c_str(), std::ios::in | std::ios::out );
    if( plik.good() )
    {
        cout << "[*] Odczyt pliku" << std::endl;
        ifstream infile(dataSource.c_str());
        string dane;
        string line;

       
        while (getline(infile, line)) {
            cout <<"[*] Odczytano wartosc : " + line << endl;
            temp+=line+"%";
            arrSize++;
        }
        tablica = stringToDynamArray(temp,"%",arrSize);
        plik.close();

        //TESTOWE
        head = new node;
        head->next = NULL;
        head->prev = NULL;
        CreateList(tablica, arrSize, head);
    }
}

void zapiszDane(node *_head){
    ofstream myfile;

    myfile.open ("out.txt");
    string line = "";

    int count = 0;
    while(_head){
        ostringstream key,countStr; 
        countStr<<count;
        key<< _head->key;
        line = "["+ countStr.str() +"] "+key.str();
        myfile << line << endl;
        _head=_head->next;
        count++;
    }

    myfile.close();
}


bool checkNextArg(vector<string> _args,int (*_iterator) , int _incr, int _action){
    int test = ((*_iterator)+_incr);
    if(_args.size() <= ((*_iterator)+_incr) ){
        action = 0;
        return true;
    }else{
        action = _action;
        key = atoi(_args[(*_iterator)+1].c_str());
        if(_incr == 2){
            index = atoi(_args[(*_iterator)+2].c_str());
        }
        (*_iterator) += _incr;
        return false;
    }
}
// Rozpoznawanie arumentow
void argsHandle(vector<string> _args){
    for (int i = 1; i < _args.size(); ++i) {
     
        if(_args[i] == "--help"){
            //--help
            usage();
            break;
        }
        
        if(_args[i] == "--dane"){
            //--dane <dane.txt>
            isArgsInvalid = checkNextArg(_args,&i,1,0);
            if(!isArgsInvalid){
                dataSource = _args[i];
            }
        }else if(_args[i] == "--znajdz"){
            //--znajdz <liczba>
            isArgsInvalid = checkNextArg(_args,&i,1,3);
        }else if(_args[i] == "--dodaj-glowa"){
            //--dodaj-ogon <LICZBA>
            isArgsInvalid = checkNextArg(_args,&i,1,2);
        }else if(_args[i] == "--dodaj-ogon"){
            //--dodaj-GLOWE <LICZBA>
            isArgsInvalid = checkNextArg(_args,&i,1,1);
        }else if(_args[i] == "--dodaj"){
            //--dodaj <liczba> <indeks>
            cout<< _args[i]<< endl;
            isArgsInvalid = checkNextArg(_args,&i,2,4);
        }else if(_args[i] == "--usun"){
            //--usun <liczba>
            cout<< _args[i]<< endl;
            isArgsInvalid = checkNextArg(_args,&i,1,5);
        }else if(_args[i] == "--usun-glowe"){
            //--usun-glowe
            action = 6;
        }else if(_args[i] == "--usun-ogon"){
            //--usun-ogon
            action = 7;
        }else if(_args[i] == "--wypisz"){
            //--wypisz
            action= 8;
        }
        else{
            cout<< "[*] Wprowadzono nieprawidlowy parametr: "+ _args[i]<< endl;
            cout<< "[*] Lista parametrow: --help"<< endl;
            break;
        }


        if(isArgsInvalid){
            printArgsError(_args);
        }
    }
}

int main(int argc, char* argv[]) {
    banner();
    if(argc > 2){
        vector<string> allArgs(argv, argv + argc);
        argsHandle(allArgs);
        if(!isArgsInvalid){
            pobierzDane();
            PrintList(head);
            if(action == 8){

            }else if (action == 6){
                head = RemoveHead(head);
                PrintList(head);
            }else if (action == 7){
                RemoveTail(head);
                PrintList(head);
            }else if (action == 5){
                DeleteIndex(head, key);
                PrintList(head);
            }else if (action == 4) {
                InsertIndex(head, key, index);
                PrintList(head);
            }else if (action == 3) {
                FindIndex(head,key);
            }else if (action == 1) {
                InsertTail(head,key);
                PrintList(head);
            }else if (action == 2) {
                head = InsertHead(head,key);
                PrintList(head);
            }

            zapiszDane(head);
        } else{
            printArgsError(allArgs);
        }
    }else{
        usage();
    }
    return 0;
}
