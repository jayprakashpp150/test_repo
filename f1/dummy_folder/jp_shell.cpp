#include<bits/stdc++.h>
#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>

#include<unistd.h>
#include<readline/readline.h>
#include<readline/history.h>
using namespace std;

mode_t compute_permission_bit(int x)
{
    mode_t mbit=0;
    int flag=0;
    return mbit;
}

void cp_command(string w)
{
    string src,dest;
    int pos=0,pos1=0,pos2=0,flag=0;

    if(w[0]=='-')
    {
        if(w[1]=='u')
        {
            if(w[2]!=' ')
            {
                cout<<"invalid command : "<<errno<<endl;
                string err(strerror(errno));
               // cout<<err<<endl;
                return;
            }
            flag=1;
            pos=3;
        }
        else
        {
            cout<<"invalid command :"<<errno<<endl;
            string err(strerror(errno));
            //cout<<err<<endl;
            return;
        }
        
    }
    pos1=w.find(' ',pos);
    if(pos1==string::npos)
    {
        cout<<"invalid command : "<<errno<<endl;
        string err(strerror(errno));
        //cout<<err<<endl;
        return;
    }

    src=w.substr(pos,pos1-pos);
    dest=w.substr(pos1+1);
    cout<<src<<endl<<dest<<endl;
    
    int sr1,sr,des;

    sr1=open(src.c_str(),O_RDONLY|O_WRONLY);
    sr=open(src.c_str(),O_RDONLY);
    if(sr1==-1)
    {
        string err(strerror(errno));
        cout<<"error in opening the "<<src<<" : "<<err<<endl;
        return;   
    }
    string filename;
    pos=src.find_last_of('/');
    if(pos==string::npos)
    {
        filename=src;

    }
    else
    {
        filename=src.substr(pos);
        cout<<filename<<endl;
    }
    des=open(dest.c_str(),O_CREAT|O_WRONLY|O_TRUNC,S_IRGRP|S_IWGRP|S_IRGRP|S_IRUSR|S_IWUSR|S_IROTH|S_IWOTH);
    if(errno==21)
    {
        dest=dest+filename;
        des=open(dest.c_str(),O_CREAT|O_WRONLY|O_TRUNC,S_IRGRP|S_IWGRP|S_IRGRP|S_IRUSR|S_IWUSR|S_IROTH|S_IWOTH);
   
    }

    if(flag==1)
    {
        FILE *fp=fopen(dest.c_str(),"r");
        FILE *fp1=fopen(src.c_str(),"r");
        char c,c1;
        if(fp==NULL)
            flag=0;
        else
        {
            while(true)
            {
                if(feof(fp1)||feof(fp))
                    break;
                fscanf(fp,"%c",&c);
                fscanf(fp1,"%c",&c1);
                if(c!=c1)
                {
                    flag=0;
                    break;
                }
            }

            fclose(fp);
            fclose(fp1);
            if(flag==1)
            {
                cout<<"same file exit"<<endl;
                return;
            }
        }
        
        
        
    }
    
    if(des==-1)
    {
        string err(strerror(errno));
        cout<<errno<<endl;
        cout<<"error in opening the "<<dest<<" : "<<err<<endl;
        return;   
    }
    int nbyte;
    char inbuf[1000];
    while((nbyte=read(sr,inbuf,1000))>0)
    {
        int wbyte=write(des,inbuf,nbyte);
        if(wbyte!=nbyte)
         {
                cout<<"error in writing file "<<endl;
            return;
         }
    }

    if(nbyte!=0)
    {  
        cout<<"file reading error"<<endl;
    return;
    }
    close(sr);
    close(des);
    
    



}


void mkdir_command(string w)
{
    char gt1[100];
    if(w!="")
    {   
        
        cout<<S_IRWXU<<endl;
        int pos_per=w.find_last_of("-m");
        
        mode_t mbit=S_IRWXU | S_IRGRP|S_IXGRP | S_IROTH | S_IXOTH;
        if(pos_per!=string::npos)
        {
            string str=w.substr(pos_per+1,w.find(' ',pos_per)-pos_per-1);
            if(str=="")
            {
                
                cout<<"missing operand" <<endl;
                return;
            }
            cout<<str<<endl;
            
            //mbit=compute_permission_bit(stoi(str));
            mbit=stoi(str,0,8);
            cout<<"per1= "<<mbit<<endl;
        }
        cout<<w<<endl;
        int len=w.length(),pos1=0,pos2=0;
        string w1;
        const char *c;
        while(w.length()>0)
        {
            if(w[0]=='"')
            {   
                    
                pos2=w.find_first_of('"',1);

                if(pos2==string::npos)
                {
                    pos2=w.length();
                }
                w1=w.substr(1,pos2-1);
                c=w1.c_str();
                string temp(c);
                cout<<temp<<endl;
                pos2++;
                
            }
            else if(w[0]=='\'')
            {
                pos2=w.find_first_of('\'',1);
                if(pos2==string::npos)
                {
                    pos2=w.length();
                }
                w1=w.substr(1,pos2-1);
                c=w1.c_str();
                string temp(c);
                cout<<temp<<endl;
                pos2++;
            }
            else
            {
                pos2=w.find_first_of(' ');
                
                if(w[pos2-1]=='\\')
                {
                    pos2=w.find_first_of(' ',pos2+1);

                }
                if(pos2==string::npos)
                {
                    pos2=w.length();
                }
                w1=w.substr(0,pos2);
                if(w1.find("\\\\")!=string::npos)
                {
                    w1="";
                }
                int post=0;
                while((post=w1.find('\\'))!=string::npos)
                {
                    w1.erase(post,1);
                }
                
                c=w1.c_str();
                string temp(c);
                cout<<temp<<endl;
            }
            w.erase(pos1,pos2+1);
            cout<<w<<endl;
            if(c[0]=='-'&&c[1]=='m')
                continue;
            if(mkdir(c,mbit))
            { 
                cout<<"command not valid"<<endl;
            }
            
            
        }
        
    
        
    }
    else
    {
        cout<<"missing argument"<<endl;
    }
            
}

string print_path()
{
    char gt[100];
    getlogin_r(gt,100);
    string path2(gt),path3;
    //cout<<path2<<"@";
    path3=path2+"@";
    gethostname(gt,100);
    string path1(gt);
    //cout<<path1<<":~";
    path3=path3+path1+":~";
    getcwd(gt,100);
    string path(gt);
    
    //cout<<path.substr(path.find(path2)+path2.length())<<"$ ";
    path3=path3+path.substr(path.find(path2)+path2.length())+"$";
    return path3;
}


int main()
{
    
    string s;

    cout<<"\n\n\n**********Terminal************"<<endl;
    
    
    char *s1;
   //set enable-keypad On
    while(true)
    {
        
        
        
        s1=readline(print_path().c_str());
        if(s1&&*s1)
            add_history(s1);
        s=s1;
        free(s1);
        //getline(cin,s);
       
        stringstream st(s);
        string w;
        getline(st,w,' ');
        if(w=="exit"||w=="EXIT")
            exit(0);
        else if(w=="ls")
            cout<<"ls"<<endl;
        else if(w=="cd")
            cout<<"cd"<<endl;
        else if(w=="cat")
            cout<<"cat"<<endl;
        else if(w=="mkdir")
        {  cout<<"mkdir"<<endl;
           
            getline(st,w);
            if(w==""||w=="mkdir")
            {
                cout<<"invalid command : missing arguments"<<endl;
                continue;
            }
            mkdir_command(w);
        }
        else if(w=="cp")
          {  cout<<"cp"<<endl;
             getline(st,w);
            if(w==""||w=="cp")
            {
                cout<<"invalid command : missing arguments"<<endl;
                continue;
            }
            cp_command(w);
          }
        else if(w=="sort")
            cout<<"sort"<<endl;
        else if(w=="grep")
            cout<<"grep"<<endl;
        else
             cout<<"not a command"<<endl;
       
        


    
    
    }




}
