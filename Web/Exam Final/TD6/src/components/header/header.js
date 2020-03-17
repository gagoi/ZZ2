import React from 'react';
import './header.css';

const FILTER_INPUT_TIMEOUT = 500;

export default class HeaderComponent extends React.Component {

  constructor(props) {
    super(props);

    this.state = { filterInputTimeout: 0, previousFilterValue : ''};

  }
   
  handleKeyUp(value) {
    if (value !== this.state.previousFilterValue) {
      clearTimeout(this.state.filterInputTimeout);
      const timer = setTimeout(() => this.props.onSearchChange(value), FILTER_INPUT_TIMEOUT);
      this.setState({ filterInputTimeout : timer, previousFilterValue: value });
    }
  }

  render() {

    return (
        <header className="app-header">

          <h1>Sports Cars</h1>
          <nav className="search">
            <input type="text" className="form-control search-filter" placeholder="Search"
              onKeyUp={ (e) => this.handleKeyUp(e.target.value) } />
          </nav>


          <section className="nav-items">

            <nav className="home" onClick={() => this.props.onMenuSelect('home')}>
              <span>⌂ Home</span>
            </nav>

            <details className="menu-top10">
              <summary>
                <nav>
                  <span>Top 10</span>
                </nav>
              </summary>

              <section>
                <nav className="top10-weight" onClick={() => this.props.onMenuSelect('weight')}>
                  <span>Weight</span>
                </nav>
                <nav className="top10-power" onClick={() => this.props.onMenuSelect('power')}>
                  <span>Power</span>
                </nav>
                <nav className="top10-ratio" onClick={() => this.props.onMenuSelect('ratio')}>
                  <span>Ratio</span>
                </nav>
              </section>
            </details>
          </section>

        </header>
    );
  }

}
