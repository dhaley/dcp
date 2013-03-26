! Copyright 01/11/07 Sun Microsystems, Inc. All Rights Reserved
! @(#)omptest.f 1.8 07/01/11 SMI
! Synthetic f90 program, used for testing openmp directives and the
!	analyzer

	program omptest

!$PRAGMA C (gethrtime, gethrvtime, init_micro_acct)

9000    format('X ', f7.3, 7x, f7.3, 4x, a)
9001    format('X Incl. Total  Incl. CPU   Name')
9002    format('      Begin... ', a)
9003    format('MHZ: ', i4)

	integer*8 gethrtime, gethrvtime
	integer *8 istart, ivstart, iend, ivend
	integer *4 getmhz, mhz

	real*8 a(400,400), b(400,400), c(400,400)

	call init_micro_acct()
	open(unit = 10, file = 'omptest.acct')

	mhz = getmhz()
	write(10,9003) mhz
	write(10, 9001)

	print *, 'Begin omptest -- various do constructs'
	n = 400
	m = 100
	call compute_set(n,m,a,b,c)

c process a set of arrays using different OMP constructs
C
c process the array with a parallel region and do's
	print 9002, 'pardo_'
	istart = gethrtime()
	ivstart = gethrvtime()
	call pardo(n,m,a,b,c)
	iend = gethrtime()
	ivend = gethrvtime()
	del = (iend - istart) / 1000000000.
	vdel = (ivend - ivstart) / 1000000000.
	write(10, 9000) del, vdel, 'pardo_'
	print 9000, del, vdel, 'pardo_'

c process the arrays with two parallel do's
	print 9002, 'pdo_'
	istart = gethrtime()
	ivstart = gethrvtime()
	call pdo(n,m,a,b,c)
	iend = gethrtime()
	ivend = gethrvtime()
	del = (iend - istart) / 1000000000.
	vdel = (ivend - ivstart) / 1000000000.
	write(10, 9000) del, vdel, 'pdo_'
	print 9000, del, vdel, 'pdo_'

c process the arrays with two parallel do's and barriers
	print 9002, 'bardo_'
	istart = gethrtime()
	ivstart = gethrvtime()
	call bardo(n,m,a,b,c)
	iend = gethrtime()
	ivend = gethrvtime()
	del = (iend - istart) / 1000000000.
	vdel = (ivend - ivstart) / 1000000000.
	write(10, 9000) del, vdel, 'bardo_'
	print 9000, del, vdel, 'bardo_'

c process the arrays with two parallel do's, dynamic scheduling
	print 9002, 'dyndo_'
	istart = gethrtime()
	ivstart = gethrvtime()
	call dyndo(n,m,a,b,c)
	iend = gethrtime()
	ivend = gethrvtime()
	del = (iend - istart) / 1000000000.
	vdel = (ivend - ivstart) / 1000000000.
	write(10, 9000) del, vdel, 'dyndo_'
	print 9000, del, vdel, 'dyndo_'

c process the arrays with parallel region and sections
	print 9002, 'parsec_'
	istart = gethrtime()
	ivstart = gethrvtime()
	call parsec(n,m,a,b,c)
	iend = gethrtime()
	ivend = gethrvtime()
	del = (iend - istart) / 1000000000.
	vdel = (ivend - ivstart) / 1000000000.
	write(10, 9000) del, vdel, 'parsec_'
	print 9000, del, vdel, 'parsec_'

c process the arrays with parallel region and sections
	print 9002, 'psec_'
	istart = gethrtime()
	ivstart = gethrvtime()
	call psec(n,m,a,b,c)
	iend = gethrtime()
	ivend = gethrvtime()
	del = (iend - istart) / 1000000000.
	vdel = (ivend - ivstart) / 1000000000.
	write(10, 9000) del, vdel, 'psec_'
	print 9000, del, vdel, 'psec_'

c process the arrays with explicit (Sun) parallelization
	print 9002, 'expldo_'
	istart = gethrtime()
	ivstart = gethrvtime()
	call expldo(n,m,a,b,c)
	iend = gethrtime()
	ivend = gethrvtime()
	del = (iend - istart) / 1000000000.
	vdel = (ivend - ivstart) / 1000000000.
	write(10, 9000) del, vdel, 'expldo_'
	print 9000, del, vdel, 'expldo_'

c process the arrays with automatic (Sun) parallelization
	print 9002, 'autodo_'
	istart = gethrtime()
	ivstart = gethrvtime()
	call autodo(n,m,a,b,c)
	iend = gethrtime()
	ivend = gethrvtime()
	del = (iend - istart) / 1000000000.
	vdel = (ivend - ivstart) / 1000000000.
	write(10, 9000) del, vdel, 'autodo_'
	print 9000, del, vdel, 'autodo_'

c process the arrays with explicit (Cray) parallelization
	print 9002, 'craydo_'
	istart = gethrtime()
	ivstart = gethrvtime()
	call craydo(n,m,a,b,c)
	iend = gethrtime()
	ivend = gethrvtime()
	del = (iend - istart) / 1000000000.
	vdel = (ivend - ivstart) / 1000000000.
	write(10, 9000) del, vdel, 'craydo_'
	print 9000, del, vdel, 'craydo_'

c process the arrays with explicit (Sun) serialization
	print 9002, 'serialdo_'
	istart = gethrtime()
	ivstart = gethrvtime()
	call serialdo(n,m,a,b,c)
	iend = gethrtime()
	ivend = gethrvtime()
	del = (iend - istart) / 1000000000.
	vdel = (ivend - ivstart) / 1000000000.
	write(10, 9000) del, vdel, 'serialdo_'
	print 9000, del, vdel, 'serialdo_'

c  Now do a sum, in various flavors
	print *, ''
	print *, 'Begin omptest -- various sum constructs'
c
c sum the arrays with a parallel reduction
	print 9002, 'redsum_'
	istart = gethrtime()
	ivstart = gethrvtime()
	call redsum(n,m,a,b,c)
	iend = gethrtime()
	ivend = gethrvtime()
	del = (iend - istart) / 1000000000.
	vdel = (ivend - ivstart) / 1000000000.
	write(10, 9000) del, vdel, 'redsum_'
	print 9000, del, vdel, 'redsum_'

c sum the arrays with an atomic operation
	print 9002, 'atomsum_'
	istart = gethrtime()
	ivstart = gethrvtime()
	call atomsum(n,m,a,b,c)
	iend = gethrtime()
	ivend = gethrvtime()
	del = (iend - istart) / 1000000000.
	vdel = (ivend - ivstart) / 1000000000.
	write(10, 9000) del, vdel, 'atomsum_'
	print 9000, del, vdel, 'atomsum_'

c sum the arrays with a critical section
	print 9002, 'critsum_'
	istart = gethrtime()
	ivstart = gethrvtime()
	call critsum(n,m,a,b,c)
	iend = gethrtime()
	ivend = gethrvtime()
	del = (iend - istart) / 1000000000.
	vdel = (ivend - ivstart) / 1000000000.
	write(10, 9000) del, vdel, 'critsum_'
	print 9000, del, vdel, 'critsum_'

c sum the arrays with explicit (Sun) parallelization/reduction
	print 9002, 'explsum_'
	istart = gethrtime()
	ivstart = gethrvtime()
	call explsum(n,m,a,b,c)
	iend = gethrtime()
	ivend = gethrvtime()
	del = (iend - istart) / 1000000000.
	vdel = (ivend - ivstart) / 1000000000.
	write(10, 9000) del, vdel, 'explsum_'
	print 9000, del, vdel, 'explsum_'

c sum the arrays with automatic (Sun) parallization
	print 9002, 'autosum_'
	istart = gethrtime()
	ivstart = gethrvtime()
	call autosum(n,m,a,b,c)
	iend = gethrtime()
	ivend = gethrvtime()
	del = (iend - istart) / 1000000000.
	vdel = (ivend - ivstart) / 1000000000.
	write(10, 9000) del, vdel, 'autosum_'
	print 9000, del, vdel, 'autosum_'

c sum the arrays with explicit (Cray) parallization
	print 9002, 'craysum_'
	istart = gethrtime()
	ivstart = gethrvtime()
	call craysum(n,m,a,b,c)
	iend = gethrtime()
	ivend = gethrvtime()
	del = (iend - istart) / 1000000000.
	vdel = (ivend - ivstart) / 1000000000.
	write(10, 9000) del, vdel, 'craysum_'
	print 9000, del, vdel, 'craysum_'

c sum the arrays with explicit (Sun) serialization
	print 9002, 'serialsum_'
	istart = gethrtime()
	ivstart = gethrvtime()
	call serialsum(n,m,a,b,c)
	iend = gethrtime()
	ivend = gethrvtime()
	del = (iend - istart) / 1000000000.
	vdel = (ivend - ivstart) / 1000000000.
	write(10, 9000) del, vdel, 'serialsum_'
	print 9000, del, vdel, 'serialsum_'


	call exit(0)
	end

	subroutine initarray(n,a,b,c)

	real*8 a(n,n), b(n,n), c(n,n)

C$omp parallel shared(a,b,c,n)
c$omp master
	do i = 1, n
	    do j = 1, n
		a(j,i) = (i * j) / (i + j)
	    enddo
	enddo
C$omp end master
c$omp single
	do i = 1, n
	    do j = 1, n
		b(j,i) = 0.
		c(j,i) = 0.
	    enddo
	enddo
c$omp end single
c$omp end parallel
	return
	end


        subroutine timerdo(n,m,a,b,c)
        real*8 a(n,n), b(n,n), c(n,n)

!	call initarray(n,a,b,c)
	   do i = 2, n-1
	      do j = 2, i
		 do k = 1, m
		    b(j,i) = b(j,i)
     &                       + a(j  ,i-1)/k     + a(j  ,i+1)/k
     &		             + a(j-1,i  )/k     + a(j+1,i  )/k
     &                       + a(j-1,i-1)/(k*k) + a(j+1,i+1)/(k*k)
     &                       + a(j-1,i+1)/(k*k) + a(j+1,i-1)/(k*k)
     		 enddo
	      enddo
	   enddo

	   do i = 2, n-1
	      do j = 2, i
		 do k = 1, m
		    c(j,i) = c(j,i)
     &                       + a(j  ,i-1)/k     + a(j  ,i+1)/k
     &		             + a(j-1,i  )/k     + a(j+1,i  )/k
     &                       - a(j-1,i-1)/(k*k) - a(j+1,i+1)/(k*k)
     &                       - a(j-1,i+1)/(k*k) - a(j+1,i-1)/(k*k)
     		 enddo
	      enddo
	   enddo
        end
