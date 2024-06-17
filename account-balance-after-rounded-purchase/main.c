int accountBalanceAfterPurchase(int purchaseAmount)
{
    int res          = 0;
    int roundedcount = purchaseAmount / 10;
    roundedcount += purchaseAmount % 10 >= 5 ? 1 : 0;
    res = 100 - roundedcount*10;

    return res;
}
