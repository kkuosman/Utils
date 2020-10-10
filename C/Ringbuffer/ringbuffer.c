/*
 * ringbuffer.c
 *
 *  Created on: May 10, 2019
 *      Author: kkuosman
 */

#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include "ringbuffer.h"

typedef struct ringBuffer {
	int32_t buffer[RING_LENGTH];
	int32_t head;
	int32_t tail;

} ringBuffer_t;

/*
 * TODO: Consider making this as a macro (if not inlined).
 */
void rb_adv_tail(ringBuffer_t* rb) {
	rb->tail = ++(rb->tail) % RING_LENGTH;
}

void rb_adv_head(ringBuffer_t* rb) {
	rb->head = ++(rb->head) % RING_LENGTH;
}

/**
 * @return bool Returns true if sample was overwritten (subject to change)
 */
int32_t rb_push(ringBuffer_t* rb, int32_t data) {
	bool retVal = false;
	/* Check if buffer is full */
	if (rb_isFull(rb)) {
		/* if full, drop the oldest by moving the tail*/
		/*rb->tail++; This would overflow*/
		rb_adv_tail(rb);
		retVal = true;
	}
	/* Move head up */
	/*rb->head = ++rb->head % RING_LENGTH;*/
	rb_adv_head(rb);
	/* Store to head */
	rb->buffer[rb->head] = data;

	return retVal;
}

/**
 * @return
 * @data the oldest value in the buffer
 */
int32_t rb_pop(ringBuffer_t* rb, int32_t* data) {
	bool retVal = false;
	*data = rb->buffer[rb->tail];
	rb_adv_tail(rb);
	return retVal;
}

int32_t rb_pushX(ringBuffer_t* rb, int32_t* data, int32_t length) {
	bool retVal = false;
	for (uint32_t i = 0; i < length; i++) {
		rb_push(rb, data[i]);
	}
	return retVal;
}

int32_t rb_popX(ringBuffer_t* rb, int32_t* data, int32_t length) {
	bool retVal = false;
	for (uint32_t i = 0; i < length; i++) {
			rb_pop(rb, &(data[i]));
	}
	return retVal;
}

/**
 * Returns true if the ring buffer is full.
 * Else returns false
 */
int32_t rb_isFull(ringBuffer_t* rb) {
	bool retVal = false;
	if ((rb->head +1)%RING_LENGTH == rb->tail) {
		retVal == true;
	}
	return retVal;
}

/**
 * Returns true if the ring buffer is empty.
 * Else returns false
 */
int32_t rb_isEmpty(ringBuffer_t* rb) {
	bool retVal = false;
	if (rb->head == rb->tail) {
		retVal = true;
	}
	return retVal;
}

int32_t runtests() {
	ringBuffer_t ring;
	int32_t data = 0;
	int32_t datarr[] = {0,1,2,3,4,5,6,7};
	assert(rb_isEmpty(&ring));

	data = 1;
	rb_push(&ring, data);
	assert(!rb_isEmpty(&ring));

	data = 0;
	assert(data == 0);
	rb_pop(&ring, &data);
	assert(data == 1);
	assert(rb_isEmpty(&ring));

	for (int32_t i = 0; i < RING_LENGTH/8; i++)
		rb_pushX(&ring, datarr, 8);
	assert(rb_isFull(&ring));



}
