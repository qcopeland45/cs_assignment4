./newShape < test.txt > testOutput.txt
diff testOutput.txt TestExpectedOutput.txt
error=$?
if [ $error -eq 0 ]
then
echo "test passed!"
elif [ $error -eq 1 ]
then
echo "test failed!"
exit 1
else
echo "test didn't run properly"
exit 1
fi
