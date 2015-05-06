package expression;

import java.util.HashSet;
import java.util.Set;

public class Atome extends Expression {

	private String name;

	public Atome(String s) {
		this.name = new String(s);
	}

	public boolean evalue() throws RuntimeException {
		throw new RuntimeException("L'expression ne peut pas être évaluée car elle contient (au moins) l'atome "+name);
	}

	public Set<String> atomes() {
		Set<String> s = new HashSet<String>();
		s.addAll(name);
		return s;
	}

	public Expression remplace(String s, boolean b) {
		if (name==s)
			name="true";
		else
			name="false";
	}

	public Expression simplifier(){
		return this;
	}

}
