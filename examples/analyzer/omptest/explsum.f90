c Copyright 02/04/2000 Sun Microsystems, Inc. All Rights Reserved

        subroutine explsum(n,m,a,b,c)
        real*8 a(n,n), b(n,n), c(n,n), sum, t

	sum = 0
C$par doall shared(a,b,c,m,n) private(i,j,k,t) reduction(sum)
	do k = 1, m
	    do i = 1, n
		do j = 1, n
		   t = (a(j,i) + b(i,j) + c(i,j))/k
		   sum = sum + t
		enddo
	    enddo
	enddo

	print 900, sum
900	format('explsum: ', e12.6)
	return
        end
