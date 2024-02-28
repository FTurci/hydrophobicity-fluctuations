#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <folder_path>\n";
        return 1;
    }
    std::string folderPath = argv[1];
    std::cout << "Folder path: " << folderPath << std::endl;

    std::ifstream file((folderPath + "/tj.xyz").c_str()); // Open the file for reading
    if (!file.is_open())
    {
        std::cerr << "Error opening the input file." << std::endl;
        return 1;
    }

    std::ofstream fout((folderPath + "/profiles.txt").c_str(), std::ios::out);

    if (!fout.is_open())
    {
        std::cerr << "Error opening the output file." << std::endl;
        return 1;
    }

    int N = 15877;
    int skip_blocks = 0;
    int num_blocks = 20001;

    std::string line;
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
    for (int i = 0; i < skip_blocks; ++i)
    {
        for (int linenum = 0; linenum < N + 9; ++linenum)
            std::getline(file, line);
    }

    for (int i = 0; i < num_blocks; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            std::getline(file, line);
            // std::cout<<"ignore "<<line<<std::endl;
        }
        std::cout << "i " << i << std::endl;
        counts.assign(nbins, 0);

        for (int linenum = 0; linenum < N; ++linenum)
        {
            file >> std::ws >> type >> x >> y >> z;

            // distance from the origin
            r = sqrt(x * x + y * y + z * z);

            int bin_index = static_cast<int>(r / bin_width);

            if (bin_index * bin_width < max_distance)
            {
                // std::cout<<"here"<<std::endl;
                counts[bin_index] += 1.0;
            }
        }
        // std::cout<<"last line "
        //         <<x<<" "
        //         <<y<<" "
        //         <<z<<" "
        //         <<r<<" "
        //         <<std::endl;

        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // write to file
        fout << "# frame " << i << std::endl;

        for (int b = 0; b < nbins; b++)
        {

            edge_left = b * bin_width;
            edge_right = (b + 1) * bin_width;
            bin_vol = bin_width * 4 * M_PI * edge_left * edge_left;

            fout << edge_left + bin_width * 0.5 << " " << counts[b] / bin_vol << std::endl;
        }
    }

    // Close the file (not necessary since file object is destroyed when it goes out of scope)
    fout.close();
    file.close();
    return 0;
}
