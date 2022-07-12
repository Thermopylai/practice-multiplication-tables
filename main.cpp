#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <iomanip>

class  Question{
    private :
        size_t m_a{};
        size_t m_b{};
        size_t m_result{};
        size_t m_input{};
        inline static size_t m_score{};
        
    public :

        Question(const size_t& min1, const size_t& max1, const size_t& min2, const size_t& max2){
            m_a = random_gen(min1, max1);
            m_b = random_gen(min2, max2);
            m_result = m_a * m_b;
            std::cout << "What is " << m_a << " * " << m_b << "? ";
            std::cin >> m_input;
            score();
        }

        size_t random_gen(const size_t& min, const size_t& max){
            std::vector<size_t> a;
            for (size_t i{min}; i < (max + 1); ++i){
                a.push_back(i);
            }
            return a[static_cast<size_t>((std::rand() % std::size(a)))];
        }
       
        void score(){
            if (m_result == m_input){
                ++m_score;
                std::cout << "Correct!" << std::endl;
            } else {
                std::cout << "Wrong answer! " << m_a << " * " << m_b << " = " << m_result << std::endl;
            }
        }

        static void print_score(const size_t& iterations){
            std::cout << "You scored : " << m_score << " / " << iterations << std::endl;
        }

        static void print_info(const Question& q){
            std::cout << q.m_a << " * " << q.m_b << " = " << q.m_result << ". Your answer : " << q.m_input << std::endl; 
        }

        static void reset_score(){
            if (m_score != 0){
                m_score = 0;
            }
        }
};

int main(){
    std::srand(std::time(0)); //Unique seed for the random number generator
    size_t min1, max1, min2, max2;
    size_t iterations;
    std::vector<Question> questions;
    bool end {false};

    while (end == false){
        std::cout << "Enter min value for the 1st operand : ";
        std::cin >> min1;
        std::cout << "Enter max value for the 1st operand : "; 
        std::cin >> max1;
        std::cout << "Enter min value for the 2nd operand : ";
        std::cin >> min2;
        std::cout << "Enter max value for the 2nd operand : "; 
        std::cin >> max2;
        std::cout << "Enter the number of questions : ";
        std::cin >> iterations;

        //Delete leftovers before a new attempt
        if (std::size(questions) != 0){
            questions.clear();
        }
        
        //Reset score to '0' before a new attempt
        Question::reset_score();

        for (size_t i{}; i < iterations; ++i){
            std::cout << i + 1 << " : ";
            Question q(min1, max1, min2, max2);
            questions.push_back(q);
        }
    
        std::cout << "-----------------------------" << std::endl;
    
        for (size_t i{}; i < iterations; ++i){
            std::cout << i + 1 << " : ";
            Question::print_info(questions[i]);
        }
    
        std::cout << "-----------------------------" << std::endl;

        Question::print_score(iterations);

        std::cout << "Try again? (y/n) : ";
        char go_on;
        std::cin >> go_on;
        end = ((go_on == 'Y') || (go_on == 'y')) ? false : true;
    }

    std::cout << "Goodbye!";
    return 0;
}