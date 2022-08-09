
#include<regex>
#include<string>
#include<vector>

struct _wREGEX_
{
  
bool wmatch(std::wstring str,std::wstring expression)
{
    std::wsmatch wm;
    
    std::wregex str_expr (expression);
    std::regex_match(str,wm,str_expr);
    return (bool)(wm.size());
}



 [[nodiscard]] std::vector<std::wstring> wsearch(std::wstring str,std::wstring expression,bool recursive=true)
{
    std::wsmatch matched;
    std::wregex str_expr (expression);
    std::vector<std::wstring>  buffer;
    if(recursive)
    {

    while(std::regex_search(str,matched,str_expr))
    {
       if(!matched.str().length())
            break;
      buffer.push_back(matched.str()); 
      str =  matched.suffix();
    }
   
    }else if(!recursive)
    {
      std::regex_search(str,matched,str_expr);
      buffer.push_back(matched.str());  
    }
  return buffer;
}


 [[nodiscard]] std::wstring wreplace(std::wstring str,std::wstring expression,std::wstring replace)
{ 
  return std::regex_replace(str,std::wregex(expression),replace);

}

} wRegex;

struct _REGEX_
{
  
bool match(std::string str,std::string expression)
{
    std::smatch wm;
    std::regex str_expr (expression);
    std::regex_match(str,wm,str_expr);
    return (bool)(wm.size());
}



 [[nodiscard]] std::vector<std::string> search(std::string str,std::string expression,bool recursive=true)
{
    std::smatch matched;
    std::regex str_expr (expression);
    std::vector<std::string>  buffer;
    if(recursive)
    {

    while(regex_search(str,matched,str_expr))
    {
       if(!matched.str().length())
            break;
      buffer.push_back(matched.str()); 
      str =  matched.suffix();
    }
   
    }else if(!recursive)
    {
      regex_search(str,matched,str_expr);
      buffer.push_back(matched.str());  
    }
  return buffer;
}


 [[nodiscard]] std::string replace(std::string str,std::string expression,std::string replace)
{ 
  return std::regex_replace(str,std::regex(expression),replace);

}

} Regex;
