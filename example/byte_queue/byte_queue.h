/*****************************************************************************
 *   Copyright(C)2009-2019 by GorgonMeducer<embedded_zhuoran@hotmail.com>    *
 *                                                                           *
 *  Licensed under the Apache License, Version 2.0 (the "License");          *
 *  you may not use this file except in compliance with the License.         *
 *  You may obtain a copy of the License at                                  *
 *                                                                           *
 *     http://www.apache.org/licenses/LICENSE-2.0                            *
 *                                                                           *
 *  Unless required by applicable law or agreed to in writing, software      *
 *  distributed under the License is distributed on an "AS IS" BASIS,        *
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. *
 *  See the License for the specific language governing permissions and      *
 *  limitations under the License.                                           *
 *                                                                           *
 ****************************************************************************/


#ifndef __PLOOC_EXAMPLE_BYTE_QUEUE_H__
#define __PLOOC_EXAMPLE_BYTE_QUEUE_H__

/*============================ INCLUDES ======================================*/
#include <stdint.h>
#include <stdbool.h>
#include "plooc.h"

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/


typedef struct mem_t {
    uint8_t     *pchBuffer;             //!< queue buffer
    uint16_t    hwSize;                 //!< buffer size
}mem_t;

/*! \NOTE: Make sure #include "plooc_class.h" is close to the class
 *!        definition and there is NO ANY OTHER module-interface-header file 
 *!        included in this file
 */
#define __PLOOC_CLASS_USE_STRICT_TEMPLATE__
   
#if     defined(__BYTE_QUEUE_CLASS_IMPLEMENT)
#   define __PLOOC_CLASS_IMPLEMENT
#   undef __BYTE_QUEUE_CLASS_IMPLEMENT
#elif   defined(__BYTE_QUEUE_CLASS_INHERIT)
#   define __PLOOC_CLASS_INHERIT
#   undef __BYTE_QUEUE_CLASS_INHERIT
#endif   

#include "plooc_class.h"

//! \name class byte_queue_t
//! @{
declare_class(byte_queue_t)

def_class(byte_queue_t, /*!< no inherit or implement */
    /*! no public_member */  ,/*! don't forget the comma here */
    private_member(
        implement(mem_t)                    //!< queue buffer
        void        *pTarget;               //!< user target
    )
    protected_member(
        uint16_t    hwHead;                 //!< head pointer
        uint16_t    hwTail;                 //!< tail pointer
        uint16_t    hwCount;                //!< byte count
    )
)

end_def_class(byte_queue_t) /* do not remove this for forward compatibility  */
//! @}

typedef struct byte_queue_cfg_t {
    implement(mem_t)                        //!< queue buffer
    void *      pTarget;                    //!< user target
} byte_queue_cfg_t;

//! \name interface i_byte_queue_t
//! @{
declare_method(i_byte_queue_t)

def_method(i_byte_queue_t, /*!< no inherit or implement */
    public_member (
        byte_queue_t *  (*Init)     (byte_queue_t *ptThis, byte_queue_cfg_t *ptCFG);
        bool            (*Enqueue)  (byte_queue_t *ptThis, uint8_t chByte);
        bool            (*Dequeue)  (byte_queue_t *ptThis, uint8_t *pchByte);
        uint_fast16_t   (*Count)    (byte_queue_t *ptThis);
        struct {
            void *      (*Get)      (byte_queue_t *ptThis);
            void        (*Set)      (byte_queue_t *ptThis, void *pTarget);
        }Target;
    ),   /*! don't forget the comma here */
    protected_member(
        struct {
            mem_t   (*Get)      (byte_queue_t *ptThis);
        }Buffer;
    )
)
end_def_method(i_byte_queue_t) /*do not remove this for forward compatibility */
//! @}


/*============================ GLOBAL VARIABLES ==============================*/
extern const i_byte_queue_t BYTE_QUEUE;
/*============================ PROTOTYPES ====================================*/



#endif
/* EOF */