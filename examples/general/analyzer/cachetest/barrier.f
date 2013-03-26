	subroutine barrier(sum)

	parameter (N = 4000)
	real(kind=8) A(N), B(N), sum
	integer i, j, k, num
	integer omp_get_max_threads, omp_get_thread_num
	integer niter(2)
	integer nactual(2)

	A = 10.
	call omp_set_num_threads(2)
	i = omp_get_max_threads()
c	print *,"omp_get_max_threads = ", i

	nactual(1) = 0
	nactual(2) = 0
	niter(1) = 1
	niter(2) = 1
	sum = 0
c$omp  parallel do
c$omp& schedule(static) shared (A) lastprivate(B) private(i,j,num) 
	do i = 1, N
	  A(i) = i
	  sum = sum + a(i)
	   
	  num = omp_get_thread_num()
	  nactual(num+1) = nactual(num+1) + 1
	  if( niter(num+1) .gt. 0 ) then
	    niter(num+1) = niter(num+1) -1
c	    print *, 'balanced loop = ', num
	      do j = 1, N
	         B(j) = i + j + MAXLOC(A, 1)
		sum = sum + b(j)
	      end do
	  end if
	end do

c	print *, 'iterations for thread 0 = ', nactual(1)
c	print *, 'iterations for thread 1 = ', nactual(2)

	nactual(1) = 0
	nactual(2) = 0
	niter(1) = 0
	niter(2) = 2
c$omp  parallel do
c$omp& schedule(static) shared (A) lastprivate(B) private(i,j,num) 
	do i = 1, N
	  A(i) = i
	  sum = sum + a(i)
	   
	  num = omp_get_thread_num()
	  nactual(num+1) = nactual(num+1) + 1
	  if( niter(num+1) .gt. 0 ) then
	    niter(num+1) = niter(num+1) -1
c	    print *, 'unbalanced loop = ', num
	    do j = 1, N
	       B(j) = i + j + MAXLOC(A, 1)
	       sum = sum + b(j)
	    end do
	  end if
	end do
c	print *, 'iterations for thread 0 = ', nactual(1)
c	print *, 'iterations for thread 1 = ', nactual(2)

	return

	end
