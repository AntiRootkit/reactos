

NTSTATUS
(NTAPI
*pNtGdiFlushUserBatch)(VOID);

INT
Test_NtGdiFlushUserBatch(PTESTINFO pti)
{
	PVOID pRet;
	PTEB pTeb;

    pNtGdiFlushUserBatch = (PVOID)GetProcAddress(g_hModule, "NtGdiFlushUserBatch");
    if (pNtGdiFlushUserBatch == NULL)
        return APISTATUS_NOT_FOUND;

	pTeb = NtCurrentTeb();
	ASSERT(pTeb);

	pRet = (PVOID)pNtGdiFlushUserBatch();

	TEST(pRet != 0);
	TEST(pRet == &pTeb->RealClientId);

	TEST(pTeb->GdiBatchCount == 0);
	TEST(pTeb->GdiTebBatch.Offset == 0);
	TEST(pTeb->GdiTebBatch.HDC == 0);

	/* Set up some bullshit */
	pTeb->InDbgPrint = 1;
	pTeb->GdiBatchCount = 12;
	pTeb->GdiTebBatch.Offset = 21;
	pTeb->GdiTebBatch.HDC = (HDC)123;

	pRet = (PVOID)pNtGdiFlushUserBatch();
	TEST(pRet == &pTeb->RealClientId);

	TEST(pTeb->InDbgPrint == 0);
	TEST(pTeb->GdiBatchCount == 12);
	TEST(pTeb->GdiTebBatch.Offset == 0);
	TEST(pTeb->GdiTebBatch.HDC == 0);

	return APISTATUS_NORMAL;
}
