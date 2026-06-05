#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <queue>

std::mutex mtx;                         // 互斥锁保护共享队列
std::condition_variable cv_producer;     // 生产者条件变量（队列未满时通知）
std::condition_variable cv_consumer;     // 消费者条件变量（队列非空时通知）
std::queue<int> data_queue;              // 共享数据队列
const int MAX_SIZE = 5;                  // 队列最大容量
bool finished = false;                   // 终止标志

// 生产者线程：向队列添加数据
void producer(int id) {
    for (int i = 0; i < 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx); // RAII 原则的策略使用： unique_lock 锁定互斥量， 保证锁的释放
        // 若队列满则等待消费者消费
        cv_producer.wait(lock, [] { 
            return data_queue.size() < MAX_SIZE; 
        });
        
        data_queue.push(i);
        std::cout << "Producer " << id << " produced: " << i << std::endl;
        lock.unlock();
        cv_consumer.notify_one();        // 通知一个消费者
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 模拟生产耗时
    }
    finished = true;                     // 生产结束
    cv_consumer.notify_all();            // 唤醒所有消费者
}
// 消费者线程：从队列取出数据
void consumer(int id) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        // 若队列空且未结束，则等待生产者
        cv_consumer.wait(lock, [] { 
            return !data_queue.empty() || finished; 
        });
        
        if (finished && data_queue.empty()) break; // 终止条件
        
        int data = data_queue.front();
        data_queue.pop();
        std::cout << "Consumer " << id << " consumed: " << data << std::endl;
        lock.unlock();
        cv_producer.notify_one();        // 通知一个生产者
        std::this_thread::sleep_for(std::chrono::milliseconds(150)); // 模拟消费耗时
    }
}

int main() {
    std::thread prod1(producer, 1);     // 生产者线程1
    std::thread prod2(producer, 2);     // 生产者线程2
    std::thread cons1(consumer, 1);     // 消费者线程1
    std::thread cons2(consumer, 2);     // 消费者线程2

    prod1.join();
    prod2.join();
    cons1.join();
    cons2.join();

    std::cout << "All threads finished." << std::endl;
    return 0;
}


