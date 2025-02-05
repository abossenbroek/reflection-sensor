#![no_main]
#![no_std]

use esp_backtrace as _;
use esp_hal::timer::timg::TimerGroup;
use defmt_rtt as _;
use defmt::*;

use embassy_executor::Spawner;
use embassy_time::{Duration, Timer};

#[embassy_executor::task]
async fn run() {
    loop {
        info!("Hello world from embassy using esp-hal-async!");
        Timer::after(Duration::from_millis(1_000)).await;
    }
}

#[esp_hal_embassy::main]
async fn main(spawner: Spawner) {
    info!("Starting up...");
    
    let peripherals = esp_hal::init(esp_hal::Config::default());
    
    info!("Peripherals initialized!");

    let timg0 = TimerGroup::new(peripherals.TIMG0);
    esp_hal_embassy::init(timg0.timer0);
    
    info!("Embassy initialized!");

    spawner.spawn(run()).ok();

    loop {
        info!("Main loop!");
        Timer::after(Duration::from_millis(5_000)).await;
    }
}