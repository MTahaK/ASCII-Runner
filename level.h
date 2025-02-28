#include <fstream>
#include <vector>
#include <string>

// We'll create a small level (map). '.' is empty space, '#' is terrain
// For simplicity, let's define it as a static 2D layout, or we can store it in a vector.
// Using a vector of strings is easier to define a mostly static level structure that
// I won't be modifying often.
std::vector<std::string> level1 = {
    "########################################",  // row 0
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",  // row 1
    "#...............##.....................#",  // row 2
    "#.............######...................#",  // row 3
    "#...............##..........####.......#",  // row 4
    "#.........................#####........#",  // row 5
    "#......................................#",  // row 6
    "#........######........................#",  // row 7
    "#........##............................#",  // row 8
    "#......####............................#",  // row 9
    "#......................................#",  // row 10
    "#.........####.........................#",  // row 11
    "#.........####..................###....#",  // row 12
    "#.........................####.........#",
    "#......................................#",  // row 1
    "#...............##.....................#",  // row 2
    "#.............######...................#",  // row 3
    "#...............##..........####.......#",  // row 4
    "#.........................#####........#",  // row 5
    "#......................................#",  // row 6
    "#........######........................#",  // row 7
    "#........##............................#",  // row 8
    "#......####............................#",  // row 9
    "#......................................#",  // row 10
    "#.........####.........................#",  // row 11
    "#.........####..................###....#",  // row 12
    "#.........................####.........#",  // row 13
    "########################################",  // row 14
    // If we want the game to end at row 14 for this minimal example
};

std::vector<std::string> altlevel = {
    "########################################",  // row 0
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",
    "|......................................|",  // row 1
    "|...............##.....................|",  // row 2
    "|.............######...................|",  // row 3
    "|...............##..........####.......|",  // row 4
    "|.........................#####........|",  // row 5
    "|......................................|",  // row 6
    "|........######........................|",  // row 7
    "|........##............................|",  // row 8
    "|......####............................|",  // row 9
    "|......................................|",  // row 10
    "|.........####.........................|",  // row 11
    "|.........####..................###....|",  // row 12
    "|.........................####.........|",
    "|......................................|",  // row 1
    "|...............##.....................|",  // row 2
    "|.............######...................|",  // row 3
    "|...............##..........####.......|",  // row 4
    "|.........................#####........|",  // row 5
    "|......................................|",  // row 6
    "|........######........................|",  // row 7
    "|........##............................|",  // row 8
    "|......####............................|",  // row 9
    "|......................................|",  // row 10
    "|.........####.........................|",  // row 11
    "|.........####..................###....|",  // row 12
    "|.........................####.........|",  // row 13
    "########################################",  // row 14
    // If we want the game to end at row 14 for this minimal example
};


std::vector<std::string> level2 = {
    "########################################",  // row 0
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "###########................#############",
    "############...............#############",
    "##########.................#############",
    "##########.................#############",
    "########....................############",
    "####........................############",
    "###........................############",
    "##.............................########",
    "##................................######",
    "##..................................####",
    "#####................................###",
    "###################..................###",
    "#####################.................##",
    "#####################..................#",
    "#####################..................#",
    "###################....................#",
    "###################....................#",
    "##############.........................#",
    "###########............................#",
    "#########..............................#",
    "########...............................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "#......................................#",
    "########################################",  // row 14
    // If we want the game to end at row 14 for this minimal example
};

std::vector<std::string> level3 = {
    "########################################",  // row 0
    "#......................................#",  // row 1
    "#......................................#",  // row 2
    "#......................................#",  // row 3
    "#......................................#",  // row 4
    "#......................................#",  // row 5
    "#......................................#",  // row 6
    "###########................#############",  // row 7
    "############...............#############",  // row 8
    "##########.................#############",  // row 9
    "##########.................#############",  // row 10
    "########....................############",  // row 11
    "####........................############",  // row 12
    "###........................############",  // row 13
    "##.............................########",  // row 14
    "##................................######",  // row 15
    "##..................................####",  // row 16
    "#####................................###",  // row 17
    "###################..................###",  // row 18
    "#####################.................##",  // row 19
    "#####################..................#",  // row 20
    "#####################..................#",  // row 21
    "###################....................#",  // row 22
    "###################....................#",  // row 23
    "##############.........................#",  // row 24
    "###########............................#",  // row 25
    "#########..............................#",  // row 26
    "########...............................#",  // row 27
    "#......................................#",  // row 28
    "#......................................#",  // row 29
    "#......................................#",  // row 30
    "#......................................#",  // row 31
    "#......................................#",  // row 32
    "#......................................#",  // row 33
    "#......................................#",  // row 34
    "#......................................#",  // row 35
    "########...............................#",  // row 36
    "#########..............................#",  // row 37
    "###########............................#",  // row 38
    "##############.........................#",  // row 39
    "###################....................#",  // row 40
    "#####################..................#",  // row 41
    "#####################.................##",  // row 42
    "###################..................###",  // row 43
    "#####................................###",  // row 44
    "##..................................####",  // row 45
    "##................................######",  // row 46
    "##.............................#########",  // row 47
    "###........................#############",  // row 48
    "####........................#############",  // row 49
    "########....................#############",  // row 50
    "##########.................#############",  // row 51
    "##########.................#############",  // row 52
    "############...............#############",  // row 53
    "###########................#############",  // row 54
    "#......................................#",  // row 55
    "#......................................#",  // row 56
    "#......................................#",  // row 57
    "#......................................#",  // row 58
    "#......................................#",  // row 59
    "########################################"   // row 60
};


std::vector<std::string> level4 = {
    "########################################",  // row 0
    "#......................................#",  // row 1
    "#......................................#",  // row 2
    "#......................................#",  // row 3
    "#......................................#",  // row 4
    "#......................................#",  // row 5
    "#......................................#",  // row 6
    "###########................#############",  // row 7
    "############...............#############",  // row 8
    "##########.................#############",  // row 9
    "##########.................#############",  // row 10
    "########....................############",  // row 11
    "####........................############",  // row 12
    "###........................#############",  // row 13
    "##...........................###########",  // row 14
    "##................................######",  // row 15
    "##..................................####",  // row 16
    "#####................................###",  // row 17
    "###################..................###",  // row 18
    "#####################.................##",  // row 19
    "#####################..................#",  // row 20
    "#####################..................#",  // row 21
    "###################....................#",  // row 22
    "###################....................#",  // row 23
    "##############.........................#",  // row 24
    "###########............................#",  // row 25
    "#########..............................#",  // row 26
    "########...............................#",  // row 27
    "###########....................#########",  // row 7
    "############..................##########",  // row 8
    "##########...................###########",  // row 9
    "##########...................###########",  // row 10
    "########.....................###########",  // row 11
    "####.........................###########", 
    "#......................................#",  // row 34
    "#......................................#",  // row 35
    "########...............................#",  // row 36
    "#########..............................#",  // row 37
    "###########............................#",  // row 38
    "##############.........................#",  // row 39
    "###################....................#",  // row 40
    "#####################..................#",  // row 41
    "#####################.................##",  // row 42
    "###################..................###",  // row 43
    "#####################..................#",  // row 41
    "#####################.................##",  // row 42
    "###################..................###",  // row 43
    "#####................................###",  // row 44
    "##..................................####",  // row 45
    "##................................######", // row 48
    "####.......................#############",  // row 49
    "########...................#############",  // row 50
    "##########.................#############",  // row 51
    "##########.................#############",  // row 52
    "############...............#############",  // row 53
    "###########................#############",  // row 54
    "#......................................#",  // row 55
    "#......................................#",  // row 56
    "#......................................#",  // row 57
    "#......................................#",  // row 58
    "#......................................#",  // row 59
    "####.....##.......###.......#####.....##",  // row 60
    "####.....##.......###.......#####.....##",  // row 60
    "####.....##.......###.......#####.....##",  // row 60
    "####.....##.......###.......#####.....##",  // row 60
    "####.....##.......###.......#####.....##",  // row 60
    "#......................................#",  // row 64
    "#......................................#",  // row 65
    "#......................................#",  // row 66
    "###########................#############",  // row 67
    "############...............#############",  // row 68
    "##########.................#############",  // row 69
    "##########.................#############",  // row 70
    "########....................############",  // row 71
    "####........................############",  // row 72
    "###.........................############",  // row 73
    "##..............................########",  // row 74
    "##................................######",  // row 75
    "##..................................####",  // row 76
    "#####................................###",  // row 77
    "###################..................###",  // row 78
    "#####################.................##",  // row 79
    "#####################..................#",  // row 80
    "#####################..................#",  // row 81
    "###################....................#",  // row 82
    "###################....................#",  // row 83
    "##############.........................#",  // row 84
    "###########............................#",  // row 85
    "#########..............................#",  // row 86
    "########...............................#",  // row 87
    "##############.........................#",  // row 92
    "###############....................#####",  // row 93
    "##############..................########",  // row 94
    "##############................##########",  // row 95
    "###########....................#########",  // row 96
    "#########.......................########",  // row 97
    "###########......................#######",  // row 98
    "##############...................#######",  // row 99
    "###################..............#######",  // row 100
    "#####################.............######",  // row 101
    "#####################...............####",  // row 102
    "###################..................###",  // row 103
    "#####................................###",  // row 104
    "##..................................####",  // row 105
    "##................................######",  // row 106
    "##.............................#########",  // row 107
    "###........................#############",  // row 108
    "####.......................#############",  // row 109
    "########...................#############",  // row 110
    "##########.................#############",  // row 111
    "##########.................#############",  // row 112
    "############...............#############",  // row 113
    "###########................#############",  // row 114
    "#......................................#",  // row 115
    "#......................................#",  // row 116
    "#......................................#",  // row 117
    "#......................................#",  // row 118
    "#......................................#",  // row 119
    "########################################"   // row 120
};

std::vector<std::string> level5 = {                                       
    "########################################",                  
    "##.................#####################",                  
    "##.................#####################",                  
    "####................####################",                  
    "#####.................##################",                  
    "######..................################",                  
    "########...................#############",                  
    "##################...........###########",                  
    "####################...........#########",                  
    "######################..........########",                  
    "#################...............########",                  
    "#############..................#########",                  
    "############....................########",                  
    "#############..................#########",                  
    "###############................#########",                  
    "#################.............##########",                  
    "#################.............##########",                  
    "#################...............########",                  
    "#################.................######",                  
    "#################................#######",                  
    "##############..................########",                  
    "############....................########",                  
    "###########.....................########",                  
    "#########.......................########",                  
    "#########........................#######",                  
    "#########.........................######",                  
    "###########.......................######",                  
    "###########.........................####",                  
    "################.....................###",                  
    "##################....................##",                  
    "####################................####",                  
    "#####################.............######",                  
    "#####################.............######",                  
    "####################................####",                  
    "#################................#######",                  
    "###########.......................######",                  
    "###########........................#####",                  
    "##########............................##",                  
    "#######................................#",                  
    "####...................................#",                  
    "#......................................#",                  
    "########################################",          
};

// std::vector<std::string> levelXscroll = {
//     "#############################################",               
//     "............................................#               
//     "...........................................##               
//     "...........................................#                
//     "..........................................##                
//     ".........................................##                 
//     "#.......................................##                  
//     "##.....................................##                   
//     " ##...................................##                    
//     "  ###.................................#                     
//     "    ##................................#                     
//     "     ##...............................#                     
//     "       ##.............................##                    
//     "        ###............................#                    
//     "          ##...........................##                   
//     "           ##...........................##                  
//     "            ##...........................#                  
//     "             ##..........................##                 
//     "              ##..........................##                
//     "               ##..........................##               
//     "                ##..........................##              
//     "                 ##..........................##             
//     "                  ##..........................##            
//     "                   ##..........................#            
//     "                    #..........................##           
//     "                    ##..........................#           
//     "                     #..........................#           
//     "                     #...........................#          
//     "                     #...........................#          
//     "                     #...........................##         
//     "                     ##...........................#         
//     "                      #...........................##        
//     "                      #............................#        
//     "                       #...........................##       
//     "                       ##...........................#       
//     "                         #..........................##      
//     "                         ##..........................##     
//     "                          ##..........................#     
//     "                           #..........................##    
//     "                           #...........................#    
//     "                           ##..........................#    
//     "                            #..........................#    
//     "                            #..........................#    
//     "                            ##.........................#    
//     "                             #.........................#    
//     "                             #.........................#    
//     "                             #.........................#    
//     "                             ##........................#    
//     "                              #.......................##    
//     "                              #......................##     
//     "                              #.....................##      
//     "                              #....................##       
//     "                             ##...................##        
//     "                            ##..................###         
//     "                           ##..................##           
//     "                          ##..................##            
//     "                         ##..................##             
//     "                        ##..................##              
//     "                      ###...................#               
//     "                     ##....................##               
//     "                    ##....................##                
//     "                   ##....................##                 
//     "                  ##.....................#                  
//     "                 ##.....................##                  
//     "                ##......................#                   
//     "               ##......................##                   
//     "               #.......................#                    
//     "              ##......................##                    
//     "              #.......................#                     
//     "              #.......................#                     
//     "             ##.......................#                     
//     "             #.......................##                     
//     "             #.......................#                      
//     "             #.......................#                      
//     "             #.......................#                      
//     "             #.......................#                      
//     "             #......................##                      
//     "             #......................#                       
//     "            ##......................#                       
//     "           ##.......................#                       
//     "          ##........................#                       
//     "          #........................##                       
//     "         ##........................#                        
//     "         #.........................#                        
//     "         #.........................#                        
//     "         #........................##                        
//     "         #........................#                         
//     "         #........................#                         
//     "         #........................#                         
//     "         #.......................##                         
//     "         #.......................#                          
//     "        #........................#                          
//     "        #........................#                          
//     "       ##........................#                          
//     "     ###.........................#                          
//     "    ##...........................#",                          
//     "  ##.............................##",                         
//     "  #...............................#",                         
//     " ##...............................#",                         
//     " ##################################"                    
// };

std::vector<std::string> readLevelFromFile(const std::string& filePath) {
    std::vector<std::string> lines;
    std::ifstream file(filePath);
    if (!file.is_open()) {
        // Could handle error here
        return lines;
    }
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    return lines;
}