#lang racket

(require racket/tcp)

(define server-port 12345) ; Replace with your desired port number

(define (handle-client client)
  (define input (current-input-port))
  (define output ())

  ; Handle client requests here
  ; For example, you can read from input and write to output
  (let loop ()
    (define line (read-line input))
    (unless (eof-object? line)
      (displayln (format "Received: ~a" line) output)
      (flush-output output)
      (loop))))

(define (main)
  (define server (tcp-listen server-port))

  (printf "Server listening on port ~a\n" server-port)

  (let loop ()
    (define-values (client _ ) (tcp-accept server))
    (thread (λ () (handle-client client))) ; Handle each client in a separate thread
    (loop)))

(main)