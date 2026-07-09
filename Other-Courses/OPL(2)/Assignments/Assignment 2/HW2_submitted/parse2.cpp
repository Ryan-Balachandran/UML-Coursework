
					   
//exact token names added 200226:
const string token_names[] = {"\"check\"", "\"read\"", "\"write\"", "id", "literal", "\"gets\"", "\"if\"",
"\"fi\"", "\"do\"", "\"od\"", "\"==\"", "\"<>\"", "\"<\"","\">\"", "\"<=\"","\">=\"","\"+\"", "\"-\"", "\"*\"", "\"/\"", 
				"\"(\"", "\")\"", "\"eof\"", "\"eps\""};					   


// added 200226:
static int tabNum = 0;  //to check for tabing spaces
static int hasError = 0;
static string image = "";

static token s_follow[] = {t_id, t_read, t_write, t_if, t_do, t_check, t_eof};
static token r_follow[] = {t_id, t_read, t_write, t_if, t_do, t_check, t_eof, t_fi, t_rparen};
static token e_follow[] = {t_id, t_read, t_write, t_if, t_do, t_check, t_eof, t_fi, t_rparen
                        , t_equiv, t_notEquiv, t_lt, t_gt, t_ltEquiv, t_gtEquiv};

// helper functins for display of syntax tree:
string postIndent(string str, int tab)
{
	for(int i=0; i<=tab; i++)
	{
		str = " ";
	}
	return str;
}

string preIndent(string str, int tab){
  for(int i = 0; i <= tab; i++)
  {
       str = " " + str;
  }
  return str;
}

string prefix(string str, string tail){
  if(tail == "") return str;
  for (int i = 0; i < tail.length(); ++i)
  {
    if(tail[i] == ' ')
	{
        return tail.substr(0,i)+" "+ str +" "+ tail.substr(i+1, tail.length() - i);
    }
  }
  return "prefix error";
}

//check if t is in the set[]
int contains(token t, token set[]){
  int i = 0;
  while(set[i]){
    if (t == set[i++])
	{
        return 1;
    }
  }
  return 0;
}
// ^^^^^^^^^^^^^^^^^^^^ end added 20026;

void error()
{
     cout << "syntax error" << endl;
     exit (1);
}

string match(token expected)
{
     if (input_token == expected)
     {
          cout << "matched " << names[input_token];

          if (input_token == t_id || input_token == t_literal)
          {
               cout << ": " << token_image;
          }

          cout << endl;
          input_token = scan();
     }
     else error();
}



/*
// cxd void to string to enable display of parse tree:
string program();
string stmt_list();
string stmt();
string expr();
string expr_tail();
string term_tail();
string term();
string factor_tail();
string factor();
string add_op();
string mul_op();

string relation();   // 'R'
string relation_op(); // encompasses all of the below:
//void equivOp();    // '=='
//void notEquivOp(); // '<>'
//void ltOp();       // '<'
//void gtOp();       // '>'
//void ltEquivOp();  // '<='
//void gtEquivOp();  // '>='
//void checkOp();    // test iteration exit;
//void doOp();       // start iteration;
//void odOp();       // terminate iteration;
//void ifOp();       // start comparator block;
//void fiOp();       // end comparator block;
*/



string program()
// modifed 200226:
{
	try{
         switch (input_token)
         {
			  case t_id:
			  case t_read:
			  case t_write:
			  case t_if:
			  case t_do:
			  case t_check:
			  case t_eof:
			  {
					cout << "predict program --> stmt_list eof" << endl;
					// added 200226:
					tabNum++;
					string str1 = "(program \n" ;
					str1 = postIndent(str1, tabNum);
					str1 += "[";

					str1 += stmt_list ();
					match (t_eof);
					str1 = postIndent(str1, tabNum);
					str1 += "]\n";
					if(hasError)
					{ 
						return ""; 
					}
					return str1+")\n";
			  }
			  default:
				// added 200226:
				throw string("program");
				return "";
				//error();
		 } // ^^^^^^^^^^^^^^^^^^^^^ end swtich block;
	} // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ end try block;
    catch (string expr)
    {
		cout << " Not expecting " << names[input_token] << " in Program " << endl;
		return "";
	}	
}

string stmt_list()

// modifed 200226:

{
     switch (input_token)
     {
          case t_id:
		  case t_check:
		  case t_if:
          case t_read:
          case t_write:
          //     cout << "predict stmt_list --> stmt stmt_list" << endl;
          //     stmt();
          //     stmt_list();
          //     break;
		  case t_do:
		  {
               string str1 = "";
			   //str1 = "";
               str1 = postIndent(str1, tabNum);
			   str1 += "("+stmt();
			   str1 += stmt_list();
			   str1 = postIndent(str1, tabNum);
			   str1 += ")\n";
			   tabNum--;
			   return str1;
			   break;
		  }	   
          case t_eof:
		  {
			   tabNum--;	
               cout << "predict stmt_list --> epsilon" << endl;
               break;          /*  epsilon production */
		  }	   
          default:
		  {
			tabNum--;
			return "\n";
			//error();
		  }	
     }
}

string stmt()

// modified 200226:
{
    tabNum++;
	try {
		switch (input_token)
		{
		  case t_id:
		  {
			   cout << "predict stmt --> id gets expr" << endl;
			   match(t_id);
			   match(t_gets);
			   string str1 = "( := (id "+ image+")" + relation();//Used to be expr()
			   str1 = postIndent(str1, tabNum);
	           str1 += ")";
               tabNum--;
               return str1;
			   //expr(); << in this version "relation()" function replaces expr()
			   //break;
		  }
		  
		  case t_read:
		  {
			   cout << "predict stmt --> read id" << endl;
			   match(t_read);
			   match(t_id);
			   tabNum--;
			   return "read (id"+image+" )\n";
			   break;
		  }
			   
		  case t_write:
		  {
		       match(t_write);
			   cout << "predict stmt --> write expr" << endl;
			   string str1 = relation();// replaces expr()
               str1 = postIndent(str1, tabNum);
               tabNum--;
               return "(write " + str1 + ")\n";
			   //expr();
			   break;
		  }   
		   	 case t_if:
			 {		 
			    match(t_if);
			    //string str1 = "(if \n";
				string str1 = "(if \n";
			    str1 = postIndent(str1, tabNum);
			    str1 += relation();
			    str1 = postIndent(str1, tabNum);
			    string str2  = stmt_list();
				//str2  = stmt_list();
			    str2 = postIndent(str2, tabNum);
			    match(t_fi);
			    tabNum--;
                return str1 +"[\n"+ str2 + "])\n";
				break;
			 }		
			
			case t_do:
			{
			    match(t_do);
                string str1 = "(do\n";
                str1 += stmt_list();
                str1 = postIndent(str1, tabNum);
                match(t_od);
                tabNum--;
                return "["+ str1 + "])\n";
				break;
			}	
				
			case t_check:
			{
                match(t_check);
                string str1 = "";
                str1 = postIndent(str1, tabNum);
                str1 += relation();
                str1 = postIndent(str1, tabNum);
                tabNum--;
                return "(check\n"+str1+")\n";
				break;
			}	
				
			default:
			{
			    error();
                tabNum--;
                return "";
			}				
        } //                  end swtich block;  

	} // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ end try block;
    catch (string expr)
	{
	    hasError = 1;
        if(expr == "match") cout <<" Not expecting " << token_names[input_token] << " in Statement" <<endl;	 
        else cout << " Not expecting " << token_names[input_token] << " in " << expr << endl;
        cout << " Skipped: " << token_names[input_token] << endl;
        input_token = scan();
        while(!contains(input_token, s_follow) && input_token != t_eof)
		{
            cout << " Skipped: " << token_names[input_token] << endl;
            input_token = scan();
        }
        if(contains(input_token, s_follow))
		{
            hasError = 1;
            return "(error)\n";
        }
		else{} 
        return "";
	} //    ^^^^^^^^^^^^^^^^^^^^^^^^^^^ end catch block;   
	
} // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ end stmt block;



string expr()
{
	tabNum++;
	try
	{
	    string str1 = term();
		string str2 = term_tail();
		tabNum--;
		return prefix(str1, str2);    
    } //  end try block;
   
   catch (string expr)
   {
	    hasError = 1;
        if(expr == "match") cout <<" Not expecting " << token_names[input_token] << " in expression" <<endl;
        else cout << " Not expecting " << token_names[input_token] << " in " << expr << endl;
        cout << " Skipped: " << token_names[input_token] << endl;
	    input_token = scan();
        while(!contains(input_token, e_follow) &&input_token != t_eof)
		{
            cout << " Skipped: " << token_names[input_token] << endl;
            input_token = scan();
        }
        if(contains(input_token, e_follow)){
            hasError = 1;
            tabNum--;
            //cout << "follow token "<< names[input_token]<<" found" << endl;
            return "(error)\n";
        }
		else
		//{ } 
        //    tabNum--;
        //    return "";
		{
			tabNum--;  // no help with errors;
            return "";
		}	
			
			
    } // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ end catch block;
    //error();
    //tabNum--; // perhaps these three stmts belong inside the catch block?
    //return "";
}

string expr_tail()
{
	tabNum++;
	
    switch (input_token)
    {
		 case t_equiv:
         case t_notEquiv:
         case t_lt:
         case t_gt:
         case t_ltEquiv:
         case t_gtEquiv:
		 {
            string str1 = relation_op();
            string str2 = expr();
            tabNum--;
            return str1+" "+str2;
			break;
        }
        case t_id:
        case t_read:
        case t_write:
        case t_eof:
            tabNum--;
            return "";
			break;
        default:
            tabNum--;
            return "";
    } //             end switch block;
		 
}

string term()
{   
    try
	{
		tabNum++;
		string str1 = factor();
		string str2 = factor_tail();
		tabNum--;
		return prefix(str1, str2);
		
       
	} //              end try block;
	catch (string expr)
	{
		throw string("Term");
		tabNum--;
	}
	
	return "";
}

string term_tail()
{
  tabNum++;
  switch (input_token) {
    case t_add:
    case t_sub:
	{
        string str1 = add_op();
        str1 += " ";
        str1 += term();
        string str2 = term_tail();
        tabNum--;
        return prefix(str1,str2);
		break;
	}	
    
    case t_rparen:
    case t_id:
    case t_read:
    case t_write:
    case t_eof:
	{
      tabNum--;
      return "";          /*  epsilon production */
	  break;
	}  
    default:
      return "";
   } //               end swtich block;
}


string factor_tail()
{
	tabNum++;
	
     switch (input_token)
     {
          case t_mul:
          case t_div:
		  {
               cout << "predict factor_tail --> mul_op factor factor_tail" << endl;
               string str1 = mul_op();
               string str2 = factor();
			   str1 += str2;
			   str1 += factor_tail();
			   tabNum--;
			   return str1+"";
               //factor_tail();
               break;
		  }	   
          case t_add:
          case t_sub:
          case t_rparen:
          case t_id:
          case t_read:
          case t_write:
          case t_eof:
		  {
               cout << "predict factor_tail --> epsilon" << endl;
			   tabNum--;
			   return "";
               break;          /*  epsilon production */
		  }	   
          default:
		      return "";
		  //error();
     }
}

string factor()
{
	tabNum++;
	
     switch (input_token)
     {
          case t_id:
		  {
               cout << "predict factor --> id" << endl;
               match(t_id);
			   tabNum--;
			   string str1 = "(lit"+image+")"; // <<<<<<<<<<<< where is "lit" defined?
			   return str1;
               break;
		  }	   
          case t_literal:
		  {
               cout << "predict factor --> literal" << endl;
               match(t_literal);
			   tabNum--;
			   string str1 = "(lit"+image+")";  // <<<<<<<<<<<< where is "lit" defined?
			   //str1 = "(lit"+image+")";  // <<<<<<<<<<<< where is "lit" defined?
               break;
		  }	   
          case t_lparen:
		  {
               cout << "predict factor --> lparen expr rparen" << endl;
               match(t_lparen);
			   string str1 = relation();
			   match(t_rparen);
			   tabNum--;
               return "("+str1+")";
               break;
		  }	   
          default:
			throw string("Factor");
			tabNum--;
			return "";
			//error();
     } //                      end switch block;
}

string relation()
{
    try{
        tabNum++;
        string str2 = expr();
        string str1 = expr_tail();
        tabNum--;
      return "("+prefix(str2, str1)+ ")\n";
    }catch(string e){
	hasError = 1;
      if(e == "match") cout <<" Not expecting " << token_names[input_token] << " in Relation" <<endl;
	//print the error messages in in catch exceptions
      else cout << " Not expecting " << token_names[input_token] << " in " << e << endl;
	//print the error messages in in catch exceptions
      
      cout << " Skipped: " << token_names[input_token] << endl;
	input_token = scan();
            while(!contains(input_token, r_follow)&&input_token != t_eof){
            cout << " Skipped: " << token_names[input_token] << endl;
            input_token = scan();
            cout << input_token<<endl;
        }
        if(contains(input_token, r_follow)){
            hasError = 1;
            tabNum--;
            //cout << "follow token "<<names[input_token]<<" found" << endl;
            return "(error)\n";
        }else{} //If having reached eof
        tabNum--;
        return " eof";
      }
}


string relation_op()
{
  tabNum++;
  switch(input_token){
    case t_equiv:
        match(t_equiv);
        tabNum--;
        return "== ";
    case t_notEquiv:
        match(t_notEquiv);
        tabNum--;
        return "<> ";
    case t_lt:
        match(t_lt);
        tabNum--;
        return "< ";
    case t_gt:
        match(t_gt);
        tabNum--;
        return "> ";
    case t_ltEquiv:
        match(t_ltEquiv);
        tabNum--;
        return "<= ";
    case t_gtEquiv:
        match(t_gtEquiv);
        tabNum--;
        return ">= ";
    default:
        throw string("Relation Operation");
        tabNum--;
        return "";
    } // end switch blcok;
}


string add_op()
{
	tabNum++;
	
     switch (input_token)
     {
          case t_add:
               cout << "predict add_op --> add" << endl;
               match(t_add);
			   tabNum--;
               return"+ ";
          case t_sub:
               cout << "predict add_op --> sub" << endl;
               match(t_sub);
			   tabNum--;
               return"- ";
          default:
		      //error();
			  throw string("Arithmetic Operator");
			  tabNum--;
			  return "";
     }
}

string mul_op()
{
    tabNum++;
    
	switch (input_token)
     {
          case t_mul:
               cout << "predict mul_op --> mul" << endl;
               match(t_mul);
			   tabNum--;
			   return "* ";
               //break;
          case t_div:
               cout << "predict mul_op --> div" << endl;
               match(t_div);
			   tabNum--;
			   return "/ ";
               //break;
          default:
             tabNum--;
			 throw string("Multiplication operator");
			 return "";
			 //error();
     }
}




//---------------------------------------------------------


int main()
{
     input_token = scan();
	 
     program();
     
     return 0;
}

