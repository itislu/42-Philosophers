#include <stdio.h>

typedef struct {
    int a;
    int b;
} t_rules;

// void	modify_non_const(t_rules *rules)
// {
// 	rules->a = 3;
// 	rules->b = 4;
// }

// void	modify_const(const t_rules *rules)
// {
// 	rules->a = 3;
// 	rules->b = 4;
// }

int main() {
    t_rules my_rules = {1, 2};
    t_rules *modifiable_ptr = &my_rules;
    t_rules *const_ptr = &my_rules;

    printf("Original values: a = %d, b = %d\n", my_rules.a, my_rules.b);

    // Modifying through a non-const pointer
    const_ptr->a = 3;
    const_ptr->b = 4;
    printf("After modifying through non-const pointer: a = %d, b = %d\n", my_rules.a, my_rules.b);

    // Trying to modify through a const pointer
    // Uncommenting the following lines will cause a compile error
    // const_ptr->a = 5;
    // const_ptr->b = 6;
    // printf("After trying to modify through const pointer: a = %d, b = %d\n", my_rules.a, my_rules.b);

    return 0;
}