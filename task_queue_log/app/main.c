#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct{
    int id;                 //Mã tác vụ
    char description[100];  // Mô tả tác vụ
    int priority;           //Độ ưu tiên
} task_t;

typedef struct task_node{
    task_t task;
    struct task_node* next;    
} task_node_t;

typedef struct log_entry{
    char message[200];
    char time_stamp[30];
    struct log_entry* next;
} log_entry_t;

task_node_t* task_queue = NULL;
log_entry_t* activity_log = NULL;
int next_task_id = 1;

// Lấy thời gian hiện tại dạng string
void get_timestamp(char* buffer, size_t size) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", t);
}

// Ghi log (thêm vào danh sách)
void add_log(const char* action, task_t* task) {
    log_entry_t * new_log = (log_entry_t*) malloc(sizeof(log_entry_t));
    if(new_log == NULL) return;
    char ts[30];
    get_timestamp(ts, sizeof(ts));
    snprintf(new_log->time_stamp, sizeof(new_log->time_stamp), "%s", ts);
    if (task != NULL)
        snprintf(new_log->message, sizeof(new_log->message),
                 "%s task #%d \"%s\" (priority %d)",
                 action, task->id, task->description, task->priority);
    else
        snprintf(new_log->message, sizeof(new_log->message), "%s", action);

    new_log->next = activity_log;
    activity_log = new_log;

}
//Thêm tác vụ vào hàm đợi
void add_task(const char* description, int priority){
    task_node_t *new_node = (task_node_t*)malloc(sizeof(task_node_t));
    if(new_node == NULL) return;

    new_node->task.id = next_task_id++;
    new_node->task.priority = priority;
    strcpy(new_node->task.description, description);
    new_node->next = NULL;

    // Nếu hàng đợi trống hoặc priority nhỏ hơn (ưu tiên cao hơn) node đầu
    if(task_queue == NULL || priority < task_queue->task.priority){
        new_node->next = task_queue;
        task_queue = new_node;
    }
    else {
        task_node_t * current = task_queue;

        // đi qua tất cả node có priority < hoặc = priority mới
        // (FIFO cho cùng priority)
        while(current->next != NULL && current->next->task.priority <= priority) {
            current = current->next;
        }

        new_node->next = current->next;
        current->next = new_node;
    }

    add_log("Added", &new_node->task);
    printf("Task #%d added.\n", new_node->task.id);
}

//Xử lý tác vụ tiếp theo
void process_next_task(){
    if (task_queue == NULL) {
        printf("⚠️ No tasks to process.\n");
        return;
    }

    task_node_t* temp = task_queue;
    task_queue = task_queue->next;

    add_log("Processed", &temp->task);
    printf("Processed task #%d: %s\n", temp->task.id, temp->task.description);

    free(temp);
}

//In danh sách tác vụ
void show_tasks(){
   if (task_queue == NULL) {
        printf("Task queue is empty.\n");
        return;
    }

    printf("📌 Current Tasks:\n");
    task_node_t* current = task_queue;
    while (current != NULL) {
        printf("  - #%d [%d] %s\n", current->task.id,
               current->task.priority, current->task.description);
        current = current->next;
    }
}

//Lưu log vào file
void save_log_to_file(const char* filename){
    FILE* f = fopen(filename, "w");
    if (!f) {
        perror("Error opening log file");
        return;
    }
    log_entry_t* current = activity_log;
    while (current != NULL) {
        fprintf(f, "[%s] %s\n", current->time_stamp, current->message);
        current = current->next;
    }
    fclose(f);
}

void free_all() {
    // Giải phóng taskQueue còn sót
    task_node_t* tc = task_queue;
    while (tc) {
        task_node_t* tmp = tc;
        tc = tc->next;
        free(tmp);
    }

    // Giải phóng activityLog
    log_entry_t* lc = activity_log;
    while (lc) {
        log_entry_t* tmp = lc;
        lc = lc->next;
        free(tmp);
    }
}

//Đọc file log vào file
void show_log(){
   if (activity_log == NULL) {
        printf("No logs yet.\n");
        return;
    }

    printf("Activity Log:\n");
    log_entry_t* current = activity_log;
    while (current != NULL) {
        printf("[%s] %s\n", current->time_stamp, current->message);
        current = current->next;
    }
}

int main() {
    int choise;
    char desc[100];
    int priority;
    do{
        printf("\n=== Task queue management ===\n");
        printf("1. Add task.\n");
        printf("2. Process task.\n");
        printf("3. Show task.\n");
        printf("4. Show activity log.\n");
        printf("5. Exit.\n");
        printf("Choose: ");
        scanf("%d",&choise);
        getchar(); //clear new line
        switch (choise)
        {
        case 1:
            printf("Enter description task: ");
            fgets(desc, sizeof(desc), stdin);
            desc[strcspn(desc, "\n")] = 0; //remove newline
            printf("Enter priority (1=high, 5=low): ");
            scanf("%d", &priority);
            add_task(desc, priority);
            break;
        case 2:
            printf("2.\n");
            process_next_task();
            break;
        case 3:
            printf("3.\n");
            show_tasks();
            break;
        case 4:
            printf("4.\n");
            show_log();
            break;
        case 5:
            printf("5.\n");
            save_log_to_file("log.txt");
            printf("Logs saved. Bye!\n");
            break;
        default:
            printf("Error.\n");
            break;
        }
    } while (choise != 5);
    free_all();
    return 0;
}