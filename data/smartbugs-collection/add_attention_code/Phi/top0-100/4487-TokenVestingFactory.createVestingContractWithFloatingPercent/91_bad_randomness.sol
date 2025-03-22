 

pragma solidity ^0.4.24;

 
 
contract PredictTheBlockHashChallenge {

    struct guess{
      uint block;
      bytes32 guess;
    }

    mapping(address => guess) guesses;

    constructor() public payable {
        require(msg.value == 1 ether);
    }

    function lockInGuess(bytes32 hash) public payable {
        require(guesses[msg.sender].block == 0);
        require(msg.value == 1 ether);

        guesses[msg.sender].guess = hash;
        guesses[msg.sender].block  = block.number + 1;
    }

    function settle() public {
        require(block.number > guesses[msg.sender].block);
         
        bytes32 answer = blockhash(guesses[msg.sender].block);

        guesses[msg.sender].block = 0;
        if (guesses[msg.sender].guess == answer) {
            msg.sender.transfer(2 ether);
        }
    }
}

contract TokenVestingFactory is Ownable() {
    event VestingContractCreated(address indexed _creator, address indexed _contract);

    mapping(address => address) public investorToVesting;

    function createVestingContractWithFloatingPercent(
        address _benificiary,
        uint _cliff,
        uint _vestingPeriod,
        address _tokenAddress,
        uint[] _periodPercents	
	)
	public
    onlyOwner
	returns (address vestingContract) 
	{
        vestingContract = new TokenVestingWithFloatingPercent(
            _benificiary, 
            _cliff,
            _vestingPeriod,
            _tokenAddress,
            _periodPercents
        );
        investorToVesting[_benificiary] = vestingContract;
        emit VestingContractCreated(tx.origin, vestingContract);
    }
}

contract TokenVestingWithFloatingPercent is BaseTokenVesting {
	
    uint[] public periodPercents;

    constructor(
        address _benificiary,
        uint _cliff,
        uint _vestingPeriod,
        address _tokenAddress,
        uint[] _periodPercents
    ) 
        BaseTokenVesting(_benificiary, _cliff, _vestingPeriod, _tokenAddress)
        public 
    {
        uint sum = 0;
        for (uint i = 0; i < _periodPercents.length; i++) {
            sum = sum.add(_periodPercents[i]);
        }
        require(sum == 100, 'percentage sum must be equal to 100');

        periodPercents = _periodPercents;
    }

    function release() public {
        require(vestingHasStarted, 'vesting has not started');
        uint unreleased = releasableAmount();

        require(unreleased > 0, 'released amount has to be greter than zero');
        require(token.transfer(beneficiary, unreleased), 'revert on transfer failure');
        released = released.add(unreleased);
        emit Released(unreleased);	
    }

    function releasableAmount() public view returns (uint _amount) {
        _amount = vestedAmount().sub(released);
    }

    function vestedAmount() public view returns (uint _amount) {
        uint currentBalance = token.balanceOf(this);
        uint totalBalance = currentBalance.add(released);

        if (now < cliff || !vestingHasStarted) {
            _amount = 0;
        }
        else {
            uint _periodPercentsIndex = now.sub(cliff).div(vestingPeriod);
            if (_periodPercentsIndex > periodPercents.length.sub(1)) {
                _amount = totalBalance;
            }
            else {
                if (_periodPercentsIndex >= 1) {
                    uint totalPercent = 0;
                    for (uint i = 0; i < _periodPercentsIndex - 1; i++) {
                        totalPercent = totalPercent + periodPercents[i];
                    }
                    _amount = totalBalance.mul(totalPercent).div(100);
                }
            }
        }
    }
}
