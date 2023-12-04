git add .
echo "See status? (1 for yes, any other key for no)"
read see_status
if [ "$see_status" -eq 1 ]; then
    git status
fi
echo "Enter Commit : "
read commit
git commit -m "$commit"
git push