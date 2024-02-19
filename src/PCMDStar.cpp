/*
 *   Copyright (C) 2023,2024 by Jonathan Naylor G4KLX
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

#include "PCMDStar.h"

#include "ModeDefines.h"
#include "Config.h"
#include "Debug.h"

CPCMDStar::CPCMDStar() :
m_n(0U)
{
}

CPCMDStar::~CPCMDStar()
{
}

void CPCMDStar::init(uint8_t n)
{
  m_n = n;

#if AMBE_TYPE == 3
  ambe4020.init(PCM_TO_DSTAR);
#else
  ambe3000.init(n, PCM_TO_DSTAR);
#endif
}

uint8_t CPCMDStar::input(const uint8_t* buffer, uint16_t length)
{
  if (length != PCM_DATA_LENGTH) {
    DEBUG2("PCM frame length is invalid", length);
    return 0x04U;
  }

#if AMBE_TYPE == 3
  return ambe4020.write(buffer, length);
#else
  return ambe3000.write(m_n, buffer, length);
#endif
}

uint16_t CPCMDStar::output(uint8_t* buffer)
{
#if AMBE_TYPE == 3
  bool ret = ambe4020.read(buffer);
#else
  bool ret = ambe3000.read(m_n, buffer);
#endif
  if (!ret)
    return 0U;

  return DSTAR_DATA_LENGTH;
}
