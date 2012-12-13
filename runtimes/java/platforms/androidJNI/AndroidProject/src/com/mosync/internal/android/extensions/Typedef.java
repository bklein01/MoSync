package com.mosync.internal.android.extensions;

import java.util.HashSet;

public class Typedef extends TypeDescriptor {

	private String name;
	private String typeref;
	private ExtensionModule module;

	public Typedef(ExtensionModule module, String name, String typeref) {
		this.module = module;
		this.name = name;
		this.typeref = typeref;
	}

	public String getTypeName() {
		return name;
	}

	public TypeDescriptor resolve(HashSet<String> circularCheck) {
		TypeDescriptor ref = module.getTypeDescriptor(typeref, 0, false);
		if (ref == null) {
			throw new IllegalArgumentException("Unknown type: " + typeref);
		}
		if (circularCheck.contains(name)) {
			throw new IllegalArgumentException("Circular definition of " + name);
		}
		circularCheck.add(name);
		return ref.resolve(circularCheck);
	}

	@Override
	public Class getNativeClass() {
		return resolve().getNativeClass();
	}

	@Override
	public Object convert(int[] args, int offset) {
		throw new UnsupportedOperationException("Typedefs must be resolved!");
	}

	public String toString() {
		return "name = " + resolve().toString();
	}
}