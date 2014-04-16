#include "util.h"

int Split(const char* str, const char* delimeter, vector<string>& vec)
{
    vec.clear();
    string text(str);
    string split(delimeter);
    string::size_type pos = 0;
    string::size_type next = string::npos;

    
    while( pos <= text.length()-1 )
    {
        next = text.find(delimeter, pos);
        if(next == string::npos)
        {
            
            vec.push_back( text.substr(pos));
            break;
        }
        else
        {
            if(next - pos <= 0)
                break;

            vec.push_back( text.substr(pos, next - pos) );
            pos = next + split.length();
        }
    }
    
    return vec.size();
    
}
