/*
 *   Copyright (C) 2024 by Jonathan Naylor G4KLX
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "YSFDNDStar.h"

#include "ModeDefines.h"
#include "YSFDNUtils.h"
#include "Debug.h"

CYSFDNDStar::CYSFDNDStar() :
m_n(0U),
m_state(YDNDS_NONE),
m_utils(),
m_buffer1(),
m_buffer2(),
m_len1(0U),
m_len2(0U)
{
}

CYSFDNDStar::~CYSFDNDStar()
{
}

uint8_t CYSFDNDStar::init(uint8_t n)
{
  m_n = n;

  // Create mode change frames for later
  m_len1 = m_utils.createModeChange(m_n, YSFDN_TO_PCM, m_buffer1);  
  m_len2 = m_utils.createModeChange(m_n, PCM_TO_DSTAR, m_buffer2);  

  ambe3000.init(n, YSFDN_TO_PCM);

  return 0x00U;
}

uint8_t CYSFDNDStar::input(const uint8_t* buffer, uint16_t length)
{
  if (length != YSFDN_DATA_LENGTH) {
    DEBUG2("YSF DN frame length is invalid", length);
    return 0x04U;
  }

  if (m_state != YDNDS_NONE) {
    DEBUG1("The AMBE3000 is busy");
    return 0x04U;
  }

  uint8_t ambe[10U];
  CYSFDNUtils::toMode34(buffer, ambe);

  m_state = YDNDS_STATE1;

  return ambe3000.writeAMBE(m_n, ambe);
}

uint8_t CYSFDNDStar::process()
{
  if (m_state != YDNDS_STATE1)
    return 0x00U;

  uint8_t buffer[400U];
  AD_STATE ret = ambe3000.readPCM(m_n, buffer);

  switch (ret) {
    case ADS_NO_DATA:
      return 0x00U;

    case ADS_DATA:
      // Receive PCM from YSF DN, send back to the chip and switch back to YSF DN to PCM
      ambe3000.writePCM(m_n, buffer, m_buffer1, m_len1);
      m_state = YDNDS_STATE2;
      return 0x00U;

    default:
      DEBUG1("YSFDNDStar:1: Invalid returned data type");
      m_state = YDNDS_NONE;
      return 0x06U;
  }
}

int16_t CYSFDNDStar::output(uint8_t* buffer)
{
  if (m_state != YDNDS_STATE2)
    return 0;

  AD_STATE ret = ambe3000.readAMBE(m_n, buffer);
  switch (ret) {
      case ADS_NO_DATA:
        return 0;

      case ADS_DATA:
        m_state = YDNDS_NONE;
        return DSTAR_DATA_LENGTH;

      default:
        DEBUG1("YSFDNDStar:2: Invalid returned data type");
        m_state = YDNDS_NONE;
        return -0x06;
  }
}

void CYSFDNDStar::finish()
{
  // Drain any outstanding replies from the chip
  ambe3000.drain(m_n);
}
