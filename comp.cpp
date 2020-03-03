#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
class Library{
    public:
    int days_signup;
    int n_books;
    int max_books_day;
    int id_library;
    vector <int> books_set;
    
    Library(int a,int b,int c,int i)
    {
        this->n_books=a;
        this->days_signup=b;
        this->max_books_day=c;
        this->id_library=i;
    }

};
int pre_scanned(int a,vector <int> v)
{
	for(int i=0;i<v.size();i++)
	if(v[i]==a)
	return 1;
	return 0;
}
int show_books(vector <int> books, vector <int> scores ,int max,vector <int> &scanned)
{
	ofstream outer;
	outer.open("submit.txt",std::ios_base::app);
	int m,myscore,max_index;
	myscore=0;
	for(int i=0;i<max;i++)
	{
		m=0;
		max_index=0;
		for(int j=0;j<books.size();j++)
		{
			if(scores[books[j]>=m] && !pre_scanned(books[j],scanned))
			{
				m=scores[books[j]];
				max_index=j;
			}
		}
		if(!pre_scanned(books[max_index],scanned))
		myscore+=scores[books[max_index]];
		outer<<books[max_index]<<" ";
		scores[max_index]=0;
		scanned.push_back(books[max_index]);
	}
	outer.close();
	return myscore;
}
int main()
{
    int num_library,num_books,num_days,aux,a,b,c;
    ifstream enter("b_read_on.txt",ios::in);
    ofstream outer;
    outer.open("submit.txt",std::ios_base::app);
    if(!enter)
    return 0;
    enter>>num_books;
    enter>>num_library;
    enter>>num_days;
    vector <int> score_books;
    vector <Library> librarys;
    vector <int> score_librarys;
    int used_library;
    for(double i=0;i<num_books;i++)
    {
        enter>>aux;
        score_books.push_back(aux);
    }
    for(int i=0;i<num_library;i++)
    {
        enter>>a>>b>>c;
        Library lib(a,b,c,i);
        for(int j=0;j<a;j++)
        {
            enter>>aux;
            lib.books_set.push_back(aux);
        }
        librarys.push_back(lib);
    }
    enter.close();
    c=0;
    int x;
    for(int i=0;i<num_library;i++){
        c=0;
        for(int j=0;j<librarys[i].n_books;j++){
            x=librarys[i].books_set[j];
            c+=score_books[x];
        }
        score_librarys.push_back(c);
    }
    vector <float> score_library_day;
    for(int i=0;i<num_library;i++)
    {
        score_library_day.push_back((float) ((score_librarys[i]/librarys[i].n_books)*librarys[i].max_books_day));
    }
    vector <Library> librarys_order;

    float qs=0;
    int max_index;
    for(int j=0;j<num_library;j++)
    {
    	for(int i=0;i<num_library;i++)
    	{
        	if(score_library_day[i]>qs)
        	{
            	qs=score_library_day[i];
            	max_index=i;
        	}
    	}
    	librarys_order.push_back(librarys[max_index]);
        score_library_day[max_index]=0;
        qs=0;
    }
    used_library=0;
    a=0;
    while(a<num_days && used_library<num_library)
    {
        a+=librarys_order[used_library].days_signup;
        used_library++;
    }
    vector <int> num_books_library;
    int num=0;
    int add;
    for(int i=0;i<num_library;i++)
    {
        num+=librarys_order[i].days_signup;
        add=(num_days-num)*librarys_order[i].max_books_day;
        if(add>=librarys_order[i].n_books)
        num_books_library.push_back(librarys_order[i].n_books);
        else
        num_books_library.push_back(add);
    }
    vector <int> scanned_books;
    outer<<used_library<<endl;
    int myscore=0;
    for(int i=0;i<used_library;i++)
    {
    	outer<<librarys_order[i].id_library<<" "<<num_books_library[i]<<endl;
    	myscore+=show_books(librarys_order[i].books_set,score_books,num_books_library[i],scanned_books);
    	outer<<endl;
    	cout<<myscore<<endl;
	}
	cout<<"myscore = "<<myscore<<endl;
    return 0;
}
