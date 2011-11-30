/*********************************************************\
 *  File: Color4.cpp                                     *
 *
 *  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  PixelLight is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PixelLight is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/String/RegEx.h>
#include "PLGraphics/Color/Color4.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLGraphics {


//[-------------------------------------------------------]
//[ Public static data                                    ]
//[-------------------------------------------------------]
const Color4 Color4::Null		(-1.0f, -1.0f, -1.0f, -1.0f);
const Color4 Color4::Transparent( 0.0f,  0.0f,  0.0f,  0.0f);
const Color4 Color4::Black		(static_cast<uint8>(  0),   0,   0, 255);
const Color4 Color4::White		(static_cast<uint8>(255), 255, 255, 255);
const Color4 Color4::Red		(static_cast<uint8>(255),   0,   0, 255);
const Color4 Color4::Yellow		(static_cast<uint8>(255), 255,   0, 255);
const Color4 Color4::Green		(static_cast<uint8>(  0), 128,   0, 255);
const Color4 Color4::Aqua		(static_cast<uint8>(  0), 255, 255, 255);
const Color4 Color4::Blue		(static_cast<uint8>(  0),   0, 255, 255);
const Color4 Color4::Fuchsia	(static_cast<uint8>(255),   0, 255, 255);
const Color4 Color4::Maroon		(static_cast<uint8>(128),   0,   0, 255);
const Color4 Color4::Olive		(static_cast<uint8>(128), 128,   0, 255);
const Color4 Color4::Navy		(static_cast<uint8>(  0),   0, 128, 255);
const Color4 Color4::Purple		(static_cast<uint8>(128),   0, 128, 255);
const Color4 Color4::Teal		(static_cast<uint8>(  0), 128, 128, 255);
const Color4 Color4::Gray		(static_cast<uint8>(128), 128, 128, 255);
const Color4 Color4::Silver		(static_cast<uint8>(192), 192, 192, 255);
const Color4 Color4::Lime		(static_cast<uint8>(  0), 255,   0, 255);


//[-------------------------------------------------------]
//[ Public static functions                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Swaps the RB components in the given buffer with 4 components (BGRA <-> RGBA)
*/
void Color4::SwapRB(uint8 nBuffer[], uint32 nNumOfPixels)
{
#if defined(WIN32) && !defined(WIN64) && !defined(NO_INLINE_ASM)
	// 32 Bit assembler method (Intel)
	void *p = nBuffer;				// Pointer to the buffer
	__asm							// Assembler code to follow
	{
		mov ecx, nNumOfPixels		// Counter set to dimensions of our memory block
		mov ebx, p					// Points ebx to our data (p)
		label:						// Label used for looping
			mov al, [ebx+0]			// Loads value at ebx into al
			mov ah, [ebx+2]			// Loads value at ebx+2 into ah
			mov [ebx+2], al			// Stores value in al at ebx+2
			mov [ebx+0], ah			// Stores value in ah at ebx
				
			add ebx, 4				// Moves through the data by 3 bytes
			dec ecx					// Decreases our loop counter
			jnz label				// If not zero jump back to label
	}
// [TODO] Check this: The Linux assembler version of this function is broken?
/*
#elif defined(LINUX) && !defined(NO_INLINE_ASM)
	// 32 Bit assembler method (AT&T)
	void *p = nBuffer;					// Pointer to the buffer
	__asm__ __volatile__ (	"movl  %0,%%ecx\n" : :"r"(nNumOfPixels):"%ecx");	// Counter set to dimensions of our memory block
	__asm__ __volatile__ (	"movl  %0,%%ebx\n" : :"r"(p));						// Points ebx to our data (p)
	__asm__ __volatile__ (	"label:\n\t"										// Label used for looping
			"mov 0(%ebx), %al \n\t"		// Loads value at ebx into al
			"mov 2(%ebx),%ah\n\t"		// Loads value at ebx+2 into ah
			"mov %al, 2(%ebx)\n\t"		// Stores value in al at ebx+2
			"mov %ah, 0(%ebx)\n\t"		// Stores value in ah at ebx

			"add $4,%ebx\n\t"			// Moves through the data by 3 bytes
			"dec %ecx\n\t"				// Decreases our loop counter
			"jnz label\n\t"				// If not zero jump back to label
	);*/
#else
	// C++ method
	const uint32 nNumOfElements = nNumOfPixels*4;
	for (uint32 i=0; i<nNumOfElements; i+=4) {
		const uint8 nTemp = nBuffer[i];
		nBuffer[i] = nBuffer[i+2];
		nBuffer[i+2] = nTemp;
	}
#endif
}


//[-------------------------------------------------------]
//[ Misc                                                  ]
//[-------------------------------------------------------]
/**
*  @brief
*    From string
*/
bool Color4::FromString(const String &sString)
{
	if (sString.GetLength()) {
		// Parse components
		uint32 nParsePos  = 0;
		uint32 nComponent = 0;
		static RegEx cRegEx("\\s*(\\S+)");
		while (nComponent < 4 && cRegEx.Match(sString, nParsePos)) {
			fColor[nComponent++] = cRegEx.GetResult(0).GetFloat();
			nParsePos = cRegEx.GetPosition();
		}

		// Set unused components to 0
		while (nComponent < 4)
			fColor[nComponent++] = 0.0f;

		// Done
		return true;
	} else {
		// Error!
		r = g = b = a = 0.0f;
		return false;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGraphics
