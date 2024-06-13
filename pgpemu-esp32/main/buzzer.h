#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "esp_err.h"

// 定义音符频率（单位：Hz）

#define F6 1397 
#define E6 1319
#define D6 1175
#define C6 1047
#define B5 987.8
#define G7 3136
#define G6 1567
#define A7 3520
#define G5 784
#define D5 587.3


#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_HIGH_SPEED_MODE
#define LEDC_OUTPUT_IO          (18) // 使用 GPIO 18
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT // PWM 占空比分辨率
#define LEDC_DUTY               (4096) // 50% 占空比 (2^13 / 2)

void beep(int frequency, int duration_ms) {
    // 设置 PWM 信号频率
    ESP_ERROR_CHECK(ledc_set_freq(LEDC_MODE, LEDC_TIMER, frequency));
    // 启动 PWM 信号输出
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
    vTaskDelay(pdMS_TO_TICKS(duration_ms)); // 持续播放音符

    // 停止 PWM 信号输出
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, 0));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
    vTaskDelay(pdMS_TO_TICKS(100)); // 停止 0.1 秒
}
void initBuzzer()
{
    // 配置 PWM 计时器
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,         // 设置速度模式
        .timer_num        = LEDC_TIMER,        // 设置计时器编号
        .duty_resolution  = LEDC_DUTY_RES,     // 设置占空比分辨率
        .freq_hz          = 2000,              // 设置 PWM 初始频率
        .clk_cfg          = LEDC_AUTO_CLK      // 自动选择时钟源
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // 配置 PWM 通道
    ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_MODE,           // 设置速度模式
        .channel        = LEDC_CHANNEL,        // 设置通道编号
        .timer_sel      = LEDC_TIMER,          // 选择计时器
        .gpio_num       = LEDC_OUTPUT_IO,      // 设置输出 GPIO 引脚
        .duty           = 0,                   // 初始占空比为 0
        .hpoint         = 0,                   // 设置计数器的高电平点
        .intr_type      = LEDC_INTR_DISABLE    // 禁用中断
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
}
void fullpokeAlert() {

    initBuzzer();
    // 播放旋律
    int note_duration = 200; // 每个音符持续时间 0.5 秒


    beep(G5, note_duration);
    beep(G5, note_duration);
    beep(D5, note_duration);
    beep(G5, note_duration);

  
}

void fullItemAlert() {

    initBuzzer();
    // 播放旋律
    int note_duration = 100; // 每个音符持续时间 0.5 秒


    beep(F6, note_duration);
    beep(E6, note_duration);
    beep(D6, note_duration);
    beep(C6, note_duration);
    beep(B5, note_duration);
    beep(C6, note_duration);
    beep(D6, note_duration);
    beep(E6, note_duration);
    beep(F6, note_duration);
    beep(G6, note_duration*1.5);
    beep(D6, note_duration*1.8);
  
}