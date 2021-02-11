        //must use Object obj to successfully override equals (not equals(ThisClass obj))
    @Override public boolean equals(Object obj) {
        // make sure to return true if you are comparing identical instances
        if (this == obj) {
            return true;
        }
        // check if null (null returns false);
        // compare getClass() results: 
        // use getClass instead of instanceOf, to make sure all relevant
        // variables are available i.e., make sure the upcoming cast will succeed
        if ((obj == null) || (getClass() != obj.getClass())) {
            return false;
        }

        ThisClass that = (ThisClass) obj;

        // examples; make sure to check for NULL on any Object; 
        // if null, return whether this Object is also null; if not, then test for equality.
        return ((isSeedEnclosed() == that.isSeedEnclosed())
            && ((that.getType() == null) ? (getType() == null) : (getType().equals(that.getType())))
            && (getAge() == that.getAge()))
            
    }

    @Override public int hashCode() {
       
        // chain by multiply previous variable's hashcode by a prime, add next
        // use Object.hashCode(); cast to Object where possible
        // make sure to check for null; if null, use 0.

        return (isSeedEnclosed() ? 0 : 1) * 31
            + (getType() == null) ? 0 : getType().hashCode() * 31
            + ((Integer)getAge()).hashCode();
    }