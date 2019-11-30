#include "SOMO_II.h"

SOMO_II::SOMO_II(Stream& a_serial) : _my_serial(a_serial) {}

//SOMO_II::SOMO_II(HardwareSerial& a_serial) : _my_serial(a_serial)
//{
  //_my_serial.begin(9600);
  //delay(100);
//}

//SOMO_II::SOMO_II(SoftwareSerial& a_serial) : _my_serial(a_serial)
//{
  //_my_serial.begin(9600);
  //delay(100);
//}

void SOMO_II::begin(uint8_t input_media)
{
  //_my_serial.begin(9600);
  reset();
  if (input_media == SOMO_USB || input_media == SOMO_uSD) {
    // set the input media if specified
    send(SOURCE, 0x00, input_media);
  }
  setVol(15);
  // wait for the SOMO module to boot up
  delay(250);
}

s_SomoMessage SOMO_II::send(e_SomoCMD message, uint8_t para1, uint8_t para2)
{
  s_SomoMessage the_message;
  the_message.cmd = message;
  if (_feedback == true) {
    the_message.feedback = 0x01;
  } else {
    the_message.feedback = 0x00;
  }
  the_message.para1 = para1;
  the_message.para2 = para2;
  uint16_t chksum = 0xFFFF - ((uint16_t)the_message.cmd + (uint16_t)the_message.feedback + (uint16_t)the_message.para1 + (uint16_t)the_message.para2) + 1;
  the_message.checksum1 = (uint8_t)(chksum >> 8); // upper 8 bits
  the_message.checksum2 = (uint8_t)chksum; // lower 8 bits
  _my_serial.write((uint8_t*)&the_message, sizeof(the_message));
  _my_serial.flush();

  delay(50);
  s_SomoMessage reply;
  bool end_message = false;
  uint32_t last_message = millis();
  while (_my_serial.available() && end_message == false && millis() - last_message <= SOMO_SERIAL_TIMEOUT) {
    uint8_t in = _my_serial.read();
    if (in == SOMO_START_BYTE) {
      last_message = millis();
      reply.cmd = _my_serial.read();
      reply.feedback = _my_serial.read();
      reply.para1 = _my_serial.read();
      reply.para2 = _my_serial.read();
      reply.checksum1 = _my_serial.read();
      reply.checksum2 = _my_serial.read();
      reply._end = _my_serial.read();
    }
    if (reply._end == SOMO_END_BYTE) {
      // assume that the message is valid
      // TODO: validate the checksum bytes
      end_message = true;
    }
  }

  if (end_message == false) {
    s_SomoMessage empty;
    return empty;
  } else {
    return reply;
  }
}

void SOMO_II::feedback(bool is_wanted) {
  if (is_wanted == true) {
    _feedback = true;
  } else {
    _feedback = false;
  }
}

uint8_t SOMO_II::reset()
{
  s_SomoMessage reply = send(RESET);

  if (reply.cmd == SOMO_ERR) {
    return reply.para2;
  } else if (reply.cmd == SOMO_OK) {
    return SOMO_OK;
  } else {
    return 0;
  }
}

uint8_t SOMO_II::playFile(uint8_t folder, uint8_t file)
{
  s_SomoMessage reply = send(PLAY_TRACK, folder, file);

  if (reply.cmd == SOMO_ERR) {
    return reply.para2;
  } else if (reply.cmd == SOMO_OK) {
    return SOMO_OK;
  } else {
    return 0;
  }
}

uint8_t SOMO_II::playTrack(uint8_t track_num)
{
  s_SomoMessage reply = send(PLAY, 0x00, track_num);

  if (reply.cmd == SOMO_ERR) {
    return reply.para2;
  } else if (reply.cmd == SOMO_OK) {
    return SOMO_OK;
  } else {
    return 0;
  }
}

uint8_t SOMO_II::stop()
{
  s_SomoMessage reply = send(STOP);

  if (reply.cmd == SOMO_ERR) {
    return reply.para2;
  } else if (reply.cmd == SOMO_OK) {
    return SOMO_OK;
  } else {
    return 0;
  }
}

uint8_t SOMO_II::setVol(uint8_t volume_level)
{
  volume_level = constrain(volume_level, 0x00, 0x1E);
  s_SomoMessage reply = send(PLAY_TRACK, 0x00, volume_level);

  if (reply.cmd == SOMO_ERR) {
    return reply.para2;
  } else if (reply.cmd == SOMO_OK) {
    return SOMO_OK;
  } else {
    return 0;
  }
}

uint8_t SOMO_II::volUp()
{
  s_SomoMessage reply = send(VOL_UP);

  if (reply.cmd == SOMO_ERR) {
    return reply.para2;
  } else if (reply.cmd == SOMO_OK) {
    return SOMO_OK;
  } else {
    return 0;
  }
}

uint8_t SOMO_II::volDown(){
  s_SomoMessage reply = send(VOL_DOWN);

  if (reply.cmd == SOMO_ERR) {
    return reply.para2;
  } else if (reply.cmd == SOMO_OK) {
    return SOMO_OK;
  } else {
    return 0;
  }
}
