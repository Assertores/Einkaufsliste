## main
redirects to entrypoint of lib this way end to end tests can be made.

## entrypoint
1. parses start arguments
2. downloads update from github
3. patches programm from old version to new version and cleans up old files
4. run main application

```mermaid
sequenceDiagram
	main ->> entry : 
	activate entry
	entry ->> argument : argument list
	activate argument
	argument ->> entry : settings
	deactivate argument
	entry ->> update : setting
	activate update
alt found update
	update ->> entry : true
	deactivate update
	entry ->> main : -1
	Note over main,entry: we have to restart the proccess with the new executable.
	activate update
else
	update ->> entry : false
	deactivate update
	entry ->> patch : setting
	activate patch
	patch ->> entry : void
	deactivate patch
	entry ->> app : setting
	deactivate entry
	activate app
	loop until user quit
		app ->> frontend : void
		frontend ->> app : close loop?
	end
	app ->> entry : success
	deactivate app
	entry ->> main : 0
end
```