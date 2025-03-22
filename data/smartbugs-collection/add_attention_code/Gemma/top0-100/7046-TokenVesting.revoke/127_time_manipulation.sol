 

pragma solidity ^0.4.25;

contract TimedCrowdsale {
   

  function revoke(ERC20Basic token) public onlyOwner {
    require(revocable);
    require(!revoked[token]);

    uint256 balance = token.balanceOf(this);

    uint256 unreleased = releasableAmount(token);
    uint256 refund = balance.sub(unreleased);

    revoked[token] = true;

    token.safeTransfer(owner, refund);

    emit Revoked();
  }


  function isSaleFinished() view public returns (bool) {
     
    return block.timestamp >= 1546300800;
  }
}
