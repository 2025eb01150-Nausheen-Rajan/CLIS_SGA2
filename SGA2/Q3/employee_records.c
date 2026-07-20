#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

struct Employee {
    int id;
    char name[30];
    float salary;
};

int main() {

    int fd = open("employee_records.dat", O_CREAT | O_RDWR, 0644);

    if(fd < 0) {
        perror("open");
        return 1;
    }

    struct Employee e1 = {101, "Aimi", 70000};
    struct Employee e2 = {102, "Koyuki", 80000};
    struct Employee e3 = {103, "Shoko", 90000};

    write(fd, &e1, sizeof(e1));
    write(fd, &e2, sizeof(e2));
    write(fd, &e3, sizeof(e3));

    struct Employee updated = {101, "Aimi", 75000};

    lseek(fd, sizeof(struct Employee), SEEK_SET);
    write(fd, &updated, sizeof(updated));

    struct Employee temp;

    lseek(fd, 2 * sizeof(struct Employee), SEEK_SET);
    read(fd, &temp, sizeof(temp));

    printf("Retrieved Record:\n");
    printf("ID: %d\n", temp.id);
    printf("Name: %s\n", temp.name);
    printf("Salary: %.2f\n", temp.salary);

    close(fd);

    return 0;
}
