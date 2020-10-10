/*
 * ringbuffer.h
 *
 *  Created on: May 10, 2019
 *      Author: kkuosman
 */

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#define RING_LENGTH		128

struct ringBuffer;

int32_t rb_push();

int32_t rb_pop();

int32_t rb_pushX();
int32_t rb_popX();
int32_t rb_isFull();
int32_t rb_isEmpty();

int32_t runtests();

#endif /* RINGBUFFER_H_ */
