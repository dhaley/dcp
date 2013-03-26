!-----------------------------------------------------------
! Standard BLAS interface:      A(1:m) = B(1:m,1:n) * C(1:n)
!-----------------------------------------------------------
      SUBROUTINE dgemv_hi1 (transa, m, n, alpha, b, ldb,    &
     &                  c, incc, beta, a, inca)
      CHARACTER (KIND=1) :: transa
      INTEGER   (KIND=4) :: m, n, incc, inca, ldb
      REAL      (KIND=8) :: alpha, beta
      REAL      (KIND=8) :: a(1:m), b(1:ldb,1:n), c(1:n)
      INTEGER            :: i, j
      REAL      (KIND=8) :: tmr, wtime, tmrend
      COMMON/timer/ tmr

      tmrend = tmr + wtime()
      DO WHILE(wtime() < tmrend)
      a(1:m) = 0.0

      DO i = 1, m
         DO j = 1, n
            a(i) = a(i) + b(i,j) * c(j)
         END DO  
      END DO  
      END DO

      RETURN
      END
!-----------------------------------------------------------
      SUBROUTINE dgemv_hi2 (transa, m, n, alpha, b, ldb,   &
     &                   c, incc, beta, a, inca)
      CHARACTER (KIND=1) :: transa
      INTEGER   (KIND=4) :: m, n, incc, inca, ldb
      REAL      (KIND=8) :: alpha, beta
      REAL      (KIND=8) :: a(1:m), b(1:ldb,1:n), c(1:n)
      INTEGER            :: i, j
      REAL      (KIND=8) :: tmr, wtime, tmrend
      COMMON/timer/ tmr

      tmrend = tmr + wtime()
      DO WHILE(wtime() < tmrend)
      a(1:m) = 0.0

      DO j = 1, n       ! <=-----\ swapped loop indices
         DO i = 1, m    !    <=--/
            a(i) = a(i) + b(i,j) * c(j)
         END DO  
      END DO  
      END DO  

      RETURN
      END
