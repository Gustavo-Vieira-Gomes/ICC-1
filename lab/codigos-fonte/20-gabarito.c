#include <stdio.h>

int main(){
    int questions_number, students_number;

    scanf("%d", &questions_number);
    scanf("%d", &students_number);

    char gabarito[questions_number+1];
    char students_responses[students_number][questions_number+1];
    float student_grades[students_number];

    scanf("%s", gabarito);
    for(int student=0; student < students_number; student++){
        scanf("%s", students_responses[student]);
    }

    for(int response = 0; response < students_number; response++){
        int right_answers = 0;
        for(int answer = 0; answer < questions_number; answer++){
            if (gabarito[answer] == students_responses[response][answer]){
                right_answers += 1;
            }
        }
        student_grades[response] = (10.0 / questions_number)*right_answers;
    }

    for (int i = 0; i < students_number; i++){
        printf("%.2f\n", student_grades[i]);
    }
}