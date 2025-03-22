 

pragma solidity 0.4.25;

contract Overflow_Add {
    uint public balance = 1;


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


    function add(uint256 deposit) public {
         
        balance += deposit;
    }
}
