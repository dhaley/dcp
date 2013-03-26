c Copyright 02/04/2000 Sun Microsystems, Inc. All Rights Reserved

        subroutine atomsum(n,m,a,b,c)
        real*8 a(n,n), b(n,n), c(n,n), sum, t

	sum = 0
c$omp  parallel do shared(a,b,c,n) private(i,j,t)
	do k = 1, m
	    do i = 1, n
		do j = 1, n
		   t = (a(j,i) + b(i,j) + c(i,j))/k
c$omp atomic
		   sum = sum + t
		enddo
	    enddo
	enddo
c$omp  end parallel do

	print 900, sum
900	format('atomsum: ', e12.6)
	return
        end
