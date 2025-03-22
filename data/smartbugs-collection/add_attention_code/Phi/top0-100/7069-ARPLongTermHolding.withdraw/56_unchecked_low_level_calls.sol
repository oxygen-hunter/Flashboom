 

pragma solidity ^0.4.16;

contract RealOldFuckMaker {
    address fuck = 0xc63e7b1DEcE63A77eD7E4Aeef5efb3b05C81438D;
    
     
     

    using SafeERC20 for ERC20;
    using SafeMath for uint256;

    uint256 public constant WITHDRAWAL_DELAY = 480 days; // = 16 months
    ERC20 public arpToken;
    uint256 public arpDeposited;

    struct Record {
        uint256 amount;
        uint256 timestamp;
    }

    mapping (address => Record) records;

    uint256 public withdrawId = 0;
    event Withdrawal(uint256 _withdrawId, address indexed _addr, uint256 _amount);

    function withdraw() private {
        require(arpDeposited > 0);

        Record storage record = records[msg.sender];
        require(record.amount > 0);
        require(now >= record.timestamp.add(WITHDRAWAL_DELAY));
        uint256 amount = record.amount;
        delete records[msg.sender];

        arpDeposited = arpDeposited.sub(amount);

        arpToken.safeTransfer(msg.sender, amount);

        emit Withdrawal(withdrawId++, msg.sender, amount);
    }

    function makeOldFucks(uint32 number) {
        uint32 i;
        for (i = 0; i < number; i++) {
             
            fuck.call(bytes4(sha3("giveBlockReward()")));
        }
    }
}