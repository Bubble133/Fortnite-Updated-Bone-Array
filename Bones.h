FTransform GetBoneIndex(DWORD_PTR mesh, int index)
{
	DWORD_PTR bonearray;
	bonearray = driver.read<DWORD_PTR>(mesh + OFFSETS::BoneArray);

	if (bonearray == NULL)
	{
		bonearray = driver.read<DWORD_PTR>(mesh + OFFSETS::BoneArray + 0x10);  //(mesh + 0x5e8) + 0x5a));
	}
	return driver.read<FTransform>(bonearray + (index * 0x60));
}
Vector3 GetBoneWithRotation(DWORD_PTR mesh, int id)
{
	FTransform bone = GetBoneIndex(mesh, id);
	FTransform ComponentToWorld = driver.read<FTransform>(mesh + OFFSETS::ComponetToWorld);

	D3DMATRIX Matrix;
	Matrix = MatrixMultiplication(bone.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());

	return Vector3(Matrix._41, Matrix._42, Matrix._43);
}
