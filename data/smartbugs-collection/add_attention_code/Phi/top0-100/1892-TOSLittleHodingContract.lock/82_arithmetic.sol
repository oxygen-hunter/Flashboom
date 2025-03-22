 

pragma solidity ^0.4.21;

contract TokenSaleChallenge {
    mapping(address => uint256) public balanceOf;
    uint256 constant PRICE_PER_TOKEN = 1 ether;


    using SafeERC20 for ERC20;
    using SafeMath for uint;
    
    uint256 public constant HOLDING_START = 1533916800;
    ERC20 public tosToken = ERC20(0xFb5a551374B656C6e39787B1D3A03fEAb7f3a98E);
    
    mapping (address => uint256) public lockBalanceOf;
    mapping (address => uint256) public principalsRecords;
    mapping (address => uint256) public rewards;

    uint256 public totalLockPrincipal = 0;
    uint256 public totalLockAmount = 0;

    bool public isReward = false;

    function lock(uint256 lockAmount) public {

        require(lockAmount > 1 * 10 ** 18);
        require(now <= HOLDING_START); 

        uint256 reward = lockAmount.mul(20).div(100);

        require(reward <= (tosToken.balanceOf(this).sub(totalLockAmount)));
        tosToken.safeTransferFrom(msg.sender, this, lockAmount);

        lockBalanceOf[msg.sender] = lockBalanceOf[msg.sender].add(lockAmount).add(reward);
        principalsRecords[msg.sender] = principalsRecords[msg.sender].add(lockAmount);
        rewards[msg.sender] = rewards[msg.sender].add(reward);
        totalLockPrincipal = totalLockPrincipal.add(lockAmount);
        totalLockAmount = totalLockAmount.add(lockAmount).add(reward);

        if (totalLockPrincipal >= 5000000 * 10 ** 18) {
            isReward = true;
        }
    }

    function TokenSaleChallenge(address _player) public payable {
        require(msg.value == 1 ether);
    }

    function isComplete() public view returns (bool) {
        return address(this).balance < 1 ether;
    }

    function buy(uint256 numTokens) public payable {
         
        require(msg.value == numTokens * PRICE_PER_TOKEN);
         
        balanceOf[msg.sender] += numTokens;
    }

    function sell(uint256 numTokens) public {
        require(balanceOf[msg.sender] >= numTokens);

        balanceOf[msg.sender] -= numTokens;
         
        msg.sender.transfer(numTokens * PRICE_PER_TOKEN);
    }
}
