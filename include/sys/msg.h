/* Copyright (C) 1995, 1996, 1997, 1999, 2000 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU C Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* Modified for MiNTLib by Frank Naumann <fnaumann@freemint.de>.  */

#ifndef _SYS_MSG_H
# define _SYS_MSG_H 1

#ifndef	_FEATURES_H
# include <features.h>
#endif

/* Get common definition of System V style IPC.  */
#ifndef _SYS_IPC_H
# include <sys/ipc.h>
#endif

__BEGIN_DECLS

/* Get system dependent definition of `struct msqid_ds' and more.  */
#include <bits/msq.h>

#define	__need_size_t
#include <stddef.h>

/* Define types required by the standard.  */
#define	__need_time_t
#include <time.h>

#ifndef pid_t
typedef __pid_t pid_t;
# define pid_t pid_t
#endif

/* The following System V style IPC functions implement a message queue
   system.  The definition is found in XPG2.  */

#ifdef __USE_GNU
/* Template for struct to be used as argument for `msgsnd' and `msgrcv'.  */
struct msgbuf
  {
    long int mtype;		/* type of received/sent message */
    char mtext[1];		/* text of the message */
  };
#endif


/* Message queue control operation.  */
extern int msgctl (int __msqid, int __cmd, struct msqid_ds *__buf) __THROW;

/* Get messages queue.  */
extern int msgget (key_t __key, int __msgflg) __THROW;

/* Receive message from message queue.  */
extern int msgrcv (int __msqid, void *__msgp, size_t __msgsz,
		   long int __msgtyp, int __msgflg) __THROW;

/* Send message to message queue.  */
extern int msgsnd (int __msqid, __const void *__msgp, size_t __msgsz,
		   int __msgflg) __THROW;

__END_DECLS

#endif /* sys/msg.h */
