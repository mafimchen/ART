/*
 * File:   ART with forgetting Algorithm.cpp
 * Author: Chen Liu
 *
 * Created on March 16, 2013, 2:49 PM
 */

 # include < cstdlib >
 # include < iostream >
 # include < fstream >
 # include < vector >
 # include < time.h >
 # include < sys / timeb.h >

using namespace std;
const int total_tc = 100000;
const int candidate_size = 10;
const int memory_size = 10;

int main(int argc, char ** argv) {
    int temp = 0;
    vector < int > fail;
    vector < int > result;

    ifstream file;
    string input = argv[1];
    string output = argv[2];
    int runtimes = atoi(argv[3]);

    file.open(input.c_str(), ios::in);
    string line;

    int zero_check = 0;
    while (!file.eof()) {
        std::getline(file, line);
        temp = atoi(line.c_str());
        if (temp == 0 && zero_check == 0)
            fail.push_back(temp);
        if (temp > 0)
            fail.push_back(temp);
        zero_check++;
    }
    file.close();

    struct timeb stb;
    ftime( & stb);
    srand((unsigned)stb.millitm);

    for (int i = 0; i < runtimes; i++) {
        int con = 1;
        int counter = 1;
        vector < int > selected;
        vector < int > can;
        vector < int > after_forget_set;
        int number = 0;
        int next = 0;
        int array[total_tc] = {0};
        int current = 0;
        current = rand() % total_tc;

        //start process
        while (con == 1) {
            array[current] = 1;

            int mini[candidate_size] = {
                0
            };

            for (int j = 0; j < fail.size(); j++) {
                if (current == fail[j]) {
                    con = 0;
                    result.push_back(counter);
                }
            }
            selected.push_back(current);
            counter++;
            while (can.size() < candidate_size) {
                number = rand() % total_tc;

                if (array[number] == 0) {
                    array[number] = 1;
                    can.push_back(number);
                }
            }

            int forget_temp = 0;
            forget_temp = selected.size() - memory_size;

            if (forget_temp >= 0) {
                for (int n = forget_temp; n < selected.size(); n++) {
                    after_forget_set.push_back(selected[n]);
                }
            } else {
                for (int n = 0; n < selected.size(); n++)
                    after_forget_set.push_back(selected[n]);
            }

            for (int y = 0; y < can.size(); y++) {
                int min = total_tc;
                for (int z = 0; z < after_forget_set.size(); z++) {
                    int temp = after_forget_set[z] - can[y];
                    if (temp < 0)
                        temp = 0 - temp;
                    if (temp < min)
                        min = temp;
                }
                mini[y] = min;
            }

            int max = 0;
            int m_temp = 0;
            for (int m = 0; m < candidate_size; m++) {
                if (mini[m] > max) {
                    max = mini[m];
                    next = can[m];
                    m_temp = m;
                }
            }
            current = next;
            for (int m = 0; m < candidate_size; m++) {
                array[can[m]] = 0;
            }
            array[can[m_temp]] = 1;
			
            can.clear();
            after_forget_set.clear();
        }
        selected.clear();
    }

    ofstream file2;
    file2.open(output.c_str());
    for (int i = 0; i < result.size(); i++) {
        file2 << result[i] << endl;
    }
    file2.close();
}
