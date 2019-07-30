;;; Directory Local Variables
;;; For more information see (info "(emacs) Directory Variables")
((nil . ((projectile-enable-caching . t)
         (projectile-project-name . "VKEngine")
         (projectile-project-debug-cmd . "scripts\\debug.bat")
         (eval . (setq projectile-project-compilation-cmd (concat "scripts\\build.bat" " " projectile-project-name)))
         )))

;;(projectile-project-compilation-cmd . "scripts\\build.bat")
;; (concat "scripts\\build.bat " projectile-project-name ))
         ;;(projectile-project-root . "W:\\VKEngine\\")
