#ifndef SCULL_USER_H

/*
 * S 'set'
 * T 'tell'
 * G 'get' by pointer
 * Q 'query' by return value
 * X 'eXchange' switch S and G atomically
 * H 'sHift' switch T and Q atomically
 */

#define SCULL_IOC_MN 0xC7

#define SCULL_IOCRESET		_IO(SCULL_IOC_MN, 0)
#define SCULL_IOCSQUANTUM	_IOW(SCULL_IOC_MN, 1, int)
#define SCULL_IOCSQSET		_IOW(SCULL_IOC_MN, 2, int)
#define SCULL_IOCTQUANTUM	_IO(SCULL_IOC_MN, 3)
#define SCULL_IOCTQSET		_IO(SCULL_IOC_MN, 4)
#define SCULL_IOCGQUANTUM	_IOR(SCULL_IOC_MN, 5, int)
#define SCULL_IOCGQSET		_IOR(SCULL_IOC_MN, 6, int)
#define SCULL_IOCQQUANTUM	_IO(SCULL_IOC_MN, 7)
#define SCULL_IOCQQSET		_IO(SCULL_IOC_MN, 8)
#define SCULL_IOCXQUANTUM	_IOWR(SCULL_IOC_MN, 9, int)
#define SCULL_IOCXQSET		_IOWR(SCULL_IOC_MN, 10, int)
#define SCULL_IOCHQUANTUM	_IO(SCULL_IOC_MN, 11)
#define SCULL_IOCHQSET		_IO(SCULL_IOC_MN, 12)

#define SCULL_IOC_MAXNR 12

#endif /* SCULL_USER_H */
