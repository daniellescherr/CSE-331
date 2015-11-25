//
//  main.cpp
//  project4
//
//  Created by Danielle Scherr on 3/13/14.
//

#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <map>

using namespace std;

int main(int argc, char* argv[])
{
    string line;
    int is_vertex = 0, is_conflict = 0, conflict1 = 0, conflict2 = 0;
    int vertex = 0;
    map<int, string>points_map;
    
    ifstream ifs(argv[1]);
    
    while (getline (ifs, line))                        //get the file line
    {
        int point = 0;
        istringstream iss(line);
        string find_vertex, find_point;
        string assign_color;
		map<int, string>::iterator find;
        while (iss >> point)
        {
            if (is_vertex == 0)                        //point is a vertex
            {
                vertex = point;
				
				find = points_map.find(vertex);
				if (find != points_map.end())			//if it found it (it has been colored)
					find_vertex = points_map.find(vertex)->second;
                else //(find_vertex != "white" && find_vertex != "black")    //has not been colored
                {
                    if ((point % 2) == 0)            //even
                        points_map[vertex] = "white";
                    else                            //odd
                        points_map[vertex] = "black";
                    find_vertex = points_map.find(vertex)->second;
                }
                is_vertex = 1;
            }
            else                                    //its not a vertex
            {
                find_point = points_map.find(point)->second;
                find_vertex = points_map.find(vertex)->second;
                if (find_point == "white" || find_point == "black")    //has been colored
                {
                    if (find_vertex == "white")
                        assign_color = "black";
                    else
                        assign_color = "white";
                    if (find_point != assign_color)                //conflict
                    {
                        conflict1 = vertex;
                        conflict2 = point;
                        is_conflict = 1;
                    }
                }
                else                                            //has not been colored
                {
                    if (find_vertex == "white")
                        assign_color = "black";
                    else
                        assign_color = "white";
                    points_map[point] = assign_color;
                }
            }
        }
        is_vertex = 0;
    }
    for (map<int, string>::iterator iter = points_map.begin(); iter!=points_map.end(); ++iter)
        cout << iter->first << " " << iter->second << "\n";
    if (is_conflict == 1)
        cout << "CONFLICT " << conflict1 << " " << conflict2 << endl;
    if (is_conflict == 0)
        cout << "TRUE" << endl;
    else
        cout << "FALSE" << endl;
    return 0;
}