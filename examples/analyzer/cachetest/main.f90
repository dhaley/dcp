! Copyright 01/28/05 Sun Microsystems, Inc. All Rights Reserved
! @(#)main.f90 1.9 05/01/28 SMI
! Based on an example used in SunTune application optimization seminars
! by Ruud van der Pas (Sun Microsystems, Inc.)

	PROGRAM MAIN

	implicit none

	include 'libfcollector.h'

	real(kind=8), allocatable    :: a(:), b(:,:), c(:)
	real(kind=8)	         :: checksum
	real(kind=8)	         :: ts, te, wtime, ti, tmr
	real(kind=4)	         :: mflops, memsize
	integer(kind=4)	      :: n
	integer(kind=4)	      :: memstat
	character(kind=1), parameter :: transa = 'n'
	character*10 routine_name
	real   (kind=8), parameter   :: alpha=1.0D0, beta=0.0d0
	integer(kind=4), parameter   :: incc=1, inca=1
	integer(kind=4)	      :: ldb
	integer	              :: flag
	integer	              :: seedsize
	integer(kind=4)	      :: seed(8)
	common/timer/ tmr

        logical, parameter           :: binding = .FALSE.
        integer(kind=4), parameter   :: cpu = 0
        integer(kind=4)              :: pbind, getpid

        call compute_set(tmr)
        if (binding) then
            if (pbind(cpu) /= 0) then
                print*, "Process binding to processor", cpu, "failed!"
                stop
            else
                print*, "Process", getpid(), "bound P", cpu
            end if
        else
            print*, "Process", getpid(), "unbound"
        end if

	call collector_sample("initialize")

	n=6000

!     allocate the two vectors and the matrix; compute flops, etc.

	allocate ( a(1:n), STAT=memstat )
	if ( memstat /= 0 ) then
	   print *,'Fatal error in memory allocation for A'
	   stop
	end if
  
	allocate ( b(1:n,1:n), STAT=memstat )
	if ( memstat /= 0 ) then
	   print *,'Fatal error in memory allocation for B'
	   stop
	end if
  
	allocate ( c(1:n), STAT=memstat )
	if ( memstat /= 0 ) then
	   print *,'Fatal error in memory allocation for C'
	   stop
	end if
  
!	call init_arrays(a, b, c, n, seed, seedsize)

	mflops  = 2.0*n*n*1.0E-06
	memsize = 8*(n+n*n+n)/1024.0    ! KByte
	ldb     = n

! y = alpha*A*x+beta*y
! a = alpha*B*c+beta*a

	print 9000

	routine_name = 'dgemv_g1'
	call load_arrays(a,b,c,n,ti)
	call collector_sample(trim(routine_name))
	ts = wtime()
	call dgemv_g1(transa, n, n, alpha, b, ldb, c, incc, beta, a, inca)
	te = wtime() - ts
	checksum = sum(a(1:n))/(n*n)
	print 9010, routine_name, n, n, memsize, checksum, te, mflops/te, ti

	call load_arrays(a,b,c,n,ti)
	routine_name = 'dgemv_g2'
	call collector_sample(trim(routine_name))
	ts = wtime()
	call dgemv_g2(transa, n, n, alpha, b, ldb, c, incc, beta, a, inca)
	te = wtime() - ts
	checksum = sum(a(1:n))/(n*n)
	print 9010, routine_name, n, n, memsize, checksum, te, mflops/te, ti

	call load_arrays(a,b,c,n,ti)
	routine_name = 'dgemv_opt1'
	call collector_sample(trim(routine_name))
	ts = wtime()
	call dgemv_opt1(transa, n, n, alpha, b, ldb, c, incc, beta, a, inca)
	te = wtime() - ts
	checksum = sum(a(1:n))/(n*n)
	print 9010, routine_name, n, n, memsize, checksum, te, mflops/te, ti

	call load_arrays(a,b,c,n,ti)
	routine_name = 'dgemv_opt2'
	call collector_sample(trim(routine_name))
	ts = wtime()
	call dgemv_opt2(transa, n, n, alpha, b, ldb, c, incc, beta, a, inca)
	te = wtime() - ts
	checksum = sum(a(1:n))/(n*n)
	print 9010, routine_name, n, n, memsize, checksum, te, mflops/te, ti

	call load_arrays(a,b,c,n,ti)
	routine_name = 'dgemv_hi1'
	call collector_sample(trim(routine_name))
	ts = wtime()
	call dgemv_hi1(transa, n, n, alpha, b, ldb, c, incc, beta, a, inca)
	te = wtime() - ts
	checksum = sum(a(1:n))/(n*n)
	print 9010, routine_name, n, n, memsize, checksum, te, mflops/te, ti

	call load_arrays(a,b,c,n,ti)
	routine_name = 'dgemv_hi2'
	call collector_sample(trim(routine_name))
	ts = wtime()
	call dgemv_hi2(transa, n, n, alpha, b, ldb, c, incc, beta, a, inca)
	te = wtime() - ts
	checksum = sum(a(1:n))/(n*n)
	print 9010, routine_name, n, n, memsize, checksum, te, mflops/te, ti

	call load_arrays(a,b,c,n,ti)
	routine_name = 'dgemv_p1'
	call omp_set_num_threads(2)
	call collector_sample(trim(routine_name))
	ts = wtime()
	call dgemv_p1(transa, n, n, alpha, b, ldb, c, incc, beta, a, inca)
	te = wtime() - ts
	checksum = sum(a(1:n))/(n*n)
	print 9010, routine_name, n, n, memsize, checksum, te, mflops/te, ti

	call load_arrays(a,b,c,n,ti)
	routine_name = 'dgemv_p2'
	call omp_set_num_threads(2)
	call collector_sample(trim(routine_name))
	ts = wtime()
	call dgemv_p2(transa, n, n, alpha, b, ldb, c, incc, beta, a, inca)
	te = wtime() - ts
	checksum = sum(a(1:n))/(n*n)
	print 9010, routine_name, n, n, memsize, checksum, te, mflops/te, ti

	routine_name = 'barrier'
	call collector_sample(trim(routine_name))
	call barrier(checksum)

	if ( allocated(a) ) deallocate(a,STAT=memstat)
	if ( allocated(b) ) deallocate(b,STAT=memstat)
	if ( allocated(c) ) deallocate(c,STAT=memstat)

	call collector_terminate_expt()

 8000   stop
 9000 format('Timings for the MXV performance measurement'/ &
	     'Routine   ',4X,'M',1X,4X,'N',1X,3X,'Mem(KB)',    &
	     2X,'Checksum',1X,'   Time',1X,'   Mflop/s', 2x, 'Init time')
 9010 format(A,2(I5,1X),F10.2,2X,F8.5,1X,F7.3,2X,F8.2, 2X, F9.3)
	end

	subroutine init_arrays(a, b, c, n, seed, seedsize)
	real (kind=8) :: a(n), b(n,n), c(n)
	integer(kind=4)	      :: seed(8)
	integer(kind=4)	      :: seedsize
	real(kind=8)	         :: ts, te, wtime, ti

	call collector_sample('init_arrays')

!     initialize the vector and matrix to all 1.0
	b(1:n,1:n) = 1.0
	c(1:n) = 1.0

	return
	end

	subroutine load_arrays(a, b, c, n, ti)
	real (kind=8) :: a(n), b(n,n), c(n)
	real(kind=8)	         :: ts, te, wtime, ti

	ts = wtime()
	call collector_sample('load_arrays')
	b(1:n,1:n) = 1.0
	c(1:n) = 1.0
	te=wtime()
	ti = te-ts

	return
	end
