/* Arduino Library for Serial Communication with the SOMO-II MP3 decoder

 */
 #include <inttypes.h>
 #include <Arduino.h>

#ifndef somo_ii_h
#define somo_ii_h

#define SOMO_BAUD 9600 // SOMO-II is requires 9600 baud

#define SOMO_SERIAL_TIMEOUT 300

#define SOMO_NEXT 0x01
#define SOMO_PREV 0x02
#define SOMO_TRACK_NUM 0x03 // send track no. as para2
#define SOMO_VOL_UP 0x04
#define SOMO_VOL_DN 0x05
#define SOMO_SET_VOL 0x06 // send volume (0-30) as para2
#define SOMO_SET_EQ 0x07 // send eq selection (0-5) as para2
#define SOMO_REPEAT 0x08 // send track no. as para2
#define SOMO_SOURCE 0x09 // send source as para2 (SOMO_USB or SOMO_uSD)
#define SOMO_SLEEP 0x0A // send SOMO_SOURCE to wake up
#define SOMO_RESET 0x0C
#define SOMO_PLAY 0x0D
#define SOMO_PAUSE 0x0E // send play to resume
#define SOMO_FOLDER_TRACK 0x0F // send folder no. as para1, and file no. as para2
#define SOMO_CONTINUOUS_MODE 0x11
#define SOMO_STOP 0x16
#define SOMO_RANDOM_MODE 0x18
#define SOMO_REPEAT_CURRENT_MODE 0x19
#define SOMO_SINGLE_PLAY_MODE 0x20 // actual message is 0x19; with para2 = 0x01
#define SOMO_QUERY_VOL 0x43
#define SOMO_QUERY_EQ 0x44
#define SOMO_QUERY_TRACKS_USB 0x47
#define SOMO_QUERY_TRACKS_uSD 0x48
#define SOMO_CURRENT_TRACK_USB 0x4B
#define SOMO_CURRENT_TRACK_uSD 0x4C
#define SOMO_QUERY_TRACKS 0x4E // send folder number as para2

#define SOMO_NO_MEDIA 0x00
#define SOMO_USB 0x01
#define SOMO_uSD 0x02
#define SOMO_BOTH 0x03

#define SOMO_OK 0x41
#define SOMO_ERR 0x40
#define SOMO_BUSY 0x01
#define SOMO_SLEEPING 0x02
#define SOMO_SERIAL_ERR 0x03
#define SOMO_BAD_CHECKSUM 0x04
#define SOMO_OUT_OF_RANGE 0x05
#define SOMO_NOT_FOUND 0x05

#define SOMO_INSERTED 0x3A
#define SOMO_REMOVED 0x3B
#define SOMO_FINISHED_USB 0x3C
#define SOMO_FINISHED_uSD 0x3D
#define SOMO_PWR_ON 0x3F

#define SOMO_START_BYTE 0x7E
#define SOMO_END_BYTE 0xEF

typedef struct s_SomoMessage {
  uint8_t _start = SOMO_START_BYTE; // $$ = 0x7E
  uint8_t cmd = 0x00;
  uint8_t feedback = 0x00;
  uint8_t para1 = 0x00;
  uint8_t para2 = 0x00;
  uint8_t checksum1 = 0xFF;
  uint8_t checksum2 = 0xBF;
  uint8_t _end = SOMO_END_BYTE; // $0 = 0xEF
};

enum e_SomoCMD {
  NEXT = SOMO_NEXT,
  PREVIOUS = SOMO_PREV,
  SPECIFY_TRACK = SOMO_TRACK_NUM,
  VOL_UP = SOMO_VOL_UP,
  VOL_DOWN = SOMO_VOL_DN,
  SET_VOLUME = SOMO_SET_VOL,
  SET_EQ = SOMO_SET_EQ,
  PLAY = SOMO_PLAY,
  PAUSE = SOMO_PAUSE,
  PLAY_TRACK = SOMO_FOLDER_TRACK,
  STOP = SOMO_STOP,
  RESET = SOMO_RESET,
  SOURCE = SOMO_SOURCE,
};

class SOMO_II {
  private:
    Stream& _my_serial;
    int _somo_rx_pin;
    int _somo_tx_pin;
    bool _feedback = true;
  public:
    SOMO_II(Stream& a_serial);
    //SOMO_II(HardwareSerial& a_serial);
    //SOMO_II(SoftwareSerial& a_serial);
    void begin(uint8_t input_media = 0x00);
    void feedback(bool is_wanted = true);
    s_SomoMessage send(e_SomoCMD message, uint8_t para1 = 0x00, uint8_t para2 = 0x00);
    uint8_t playFile(uint8_t folder, uint8_t file);
    uint8_t playTrack(uint8_t track_num);
    uint8_t stop();
    uint8_t setVol(uint8_t volume_level);
    uint8_t volUp();
    uint8_t volDown();
    uint8_t reset();
};

#endif
