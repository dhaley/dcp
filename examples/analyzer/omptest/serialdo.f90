c Copyright 02/04/2000 Sun Microsystems, Inc. All Rights Reserved

        subroutine serialdo(n,m,a,b,c)

        real*8 a(n,n), b(n,n), c(n,n)

	call initarray(n,a,b,c)

c$par  doserial*
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

c$par  doserial*
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
