/* 
 * File:   LM35.h
 * Author: Arkadiusz
 *
 * Created on 23 listopada 2019, 19:51
 */

#ifndef LM35_H
#define	LM35_H

#ifdef	__cplusplus
extern "C" {
#endif
//------------------------------------------------------------------------------

void ADCinit();
uint8_t Get_Temperature();

//------------------------------------------------------------------------------
#ifdef	__cplusplus
}
#endif

#endif	/* LM35_H */

