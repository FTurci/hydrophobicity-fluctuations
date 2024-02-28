    #include <iostream>
    #include <fstream>
    #include <sstream>
    #include <string>
    #include <vector>
    #include <cmath>
    #include <limits>

    int main()
    {
        std::ifstream file("tj/tj.xyz"); // Open the file for reading
        std::string line;
        std::ofstream fout("tj/profiles.txt", std::ios::out);
        int N = 15877;
        int skip_blocks = 0;
        int num_blocks = 3;

        if (!file.is_open())
        {
            std::cerr << "Error opening the file." << std::endl;
            return 1;
        }

        int type;
        double x, y, z, r;

        // for the historgram

        double bin_width = 0.25;
        double bin_vol;
        int nbins = 60;
        double max_distance = bin_width * nbins;
        double edge_left, edge_right;
        std::vector<double> counts(nbins, 0);

        // skipping the warmup


        for (int i = 0; i < num_blocks; ++i)
        {           
            for (int j = 0; j < 9; ++j) {
                std::getline(file, line);
                std::cout<<"ignore "<<line<<std::endl;
            }
 
            for (int linenum = 0; linenum < N; ++linenum)
            {
                    file >> std::ws >> type>>  x>> y>>z;
                    
                    if (linenum<2 ) {
                        std::cout<<" "
                        <<x<<" "
                        <<y<<" "
                        <<z<<" "
                        <<r<<" "
                        <<std::endl;
                        }
                        
       
            }
             std::cout<<"last line "
                        <<x<<" "
                        <<y<<" "
                        <<z<<" "
                        <<r<<" "
                        <<std::endl;

            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }


        return 0;
    }
